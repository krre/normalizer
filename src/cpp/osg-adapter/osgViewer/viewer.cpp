#include "viewer.h"
#include "texturenode.h"
#include <QtQuick>
#include <osg/ShapeDrawable>
#include <osgDB/ReadFile>
#include <osgGA/MultiTouchTrackballManipulator>
#include <osg/Camera>
#include <osgViewer/Renderer>

QList<QThread*> Viewer::threads;

Viewer::Viewer()
{
    setFlag(ItemHasContents, true);
}

void Viewer::ready()
{
    m_renderThread->surface = new QOffscreenSurface();
    m_renderThread->surface->setFormat(m_renderThread->context->format());
    m_renderThread->surface->create();

    m_renderThread->moveToThread(m_renderThread);

    connect(window(), SIGNAL(sceneGraphInvalidated()), m_renderThread, SLOT(shutDown()), Qt::QueuedConnection);

    m_renderThread->start();
    update();
}

QSGNode* Viewer::updatePaintNode(QSGNode* oldNode, UpdatePaintNodeData*)
{
    TextureNode* node = static_cast<TextureNode*>(oldNode);

    if (!m_renderThread) {
        int width = window()->width();
        int height = window()->height();
        viewer = new osgViewer::Viewer;
        viewer->setSceneData(osgDB::readNodeFile("cow.osgt"));
        viewer->setCameraManipulator(new osgGA::MultiTouchTrackballManipulator);
        viewer->setUpViewerAsEmbeddedInWindow(0, 0, width, height);
        viewer->getEventQueue()->windowResize(0, 0, width, height);

        osg::Camera* camera = viewer->getCamera();
        camera->setRenderTargetImplementation(osg::Camera::FRAME_BUFFER_OBJECT);
        camera->setViewport(0, 0, width, height);
        camera->setProjectionMatrixAsPerspective(fov, width / height, zNear, zFar);
        camera->setNearFarRatio(zNearFarRatio);
        camera->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        camera->setClearColor(color);

        fboTexture = new osg::Texture2D();
        fboTexture->setTextureSize(width, height);
        fboTexture->setInternalFormat(GL_RGBA);
        fboTexture->setFilter(osg::Texture2D::MIN_FILTER,osg::Texture2D::LINEAR);
        fboTexture->setFilter(osg::Texture2D::MAG_FILTER,osg::Texture2D::LINEAR);
        fboTexture->apply(*camera->getGraphicsContext()->getState());

        camera->attach(osg::Camera::COLOR_BUFFER, fboTexture, 0, 0);

        osgViewer::Renderer* renderer = dynamic_cast<osgViewer::Renderer*>(camera->getRenderer());
        if (renderer) {
            renderer->setCameraRequiresSetUp(true);
        }

        m_renderThread = new RenderThread(QSize(width, height), viewer, fboTexture);
    }

    if (!m_renderThread->context) {
        QOpenGLContext *current = window()->openglContext();
        // Some GL implementations requres that the currently bound context is
        // made non-current before we set up sharing, so we doneCurrent here
        // and makeCurrent down below while setting up our own context.
        current->doneCurrent();

        m_renderThread->context = new QOpenGLContext();
        m_renderThread->context->setFormat(current->format());
        m_renderThread->context->setShareContext(current);
        m_renderThread->context->create();
        m_renderThread->context->moveToThread(m_renderThread);

        current->makeCurrent(window());

        QMetaObject::invokeMethod(this, "ready");
        return 0;
    }

    if (!node) {
        node = new TextureNode(window());

        /* Set up connections to get the production of FBO textures in sync with vsync on the
         * rendering thread.
         *
         * When a new texture is ready on the rendering thread, we use a direct connection to
         * the texture node to let it know a new texture can be used. The node will then
         * emit pendingNewTexture which we bind to QQuickWindow::update to schedule a redraw.
         *
         * When the scene graph starts rendering the next frame, the prepareNode() function
         * is used to update the node with the new texture. Once it completes, it emits
         * textureInUse() which we connect to the FBO rendering thread's renderNext() to have
         * it start producing content into its current "back buffer".
         *
         * This FBO rendering pipeline is throttled by vsync on the scene graph rendering thread.
         */
        connect(m_renderThread, SIGNAL(textureReady(int,QSize)), node, SLOT(newTexture(int,QSize)), Qt::DirectConnection);
        connect(node, SIGNAL(pendingNewTexture()), window(), SLOT(update()), Qt::QueuedConnection);
        connect(window(), SIGNAL(beforeRendering()), node, SLOT(prepareNode()), Qt::DirectConnection);
        connect(node, SIGNAL(textureInUse()), m_renderThread, SLOT(renderNext()), Qt::QueuedConnection);

        // Get the production of FBO textures started..
        QMetaObject::invokeMethod(m_renderThread, "renderNext", Qt::QueuedConnection);
    }

    node->setRect(boundingRect());

    return node;
}
