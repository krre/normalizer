#include "viewer.h"
#include <QtQuick>
#include <osg/ShapeDrawable>
#include <osgDB/ReadFile>

Viewer::Viewer()
{
    setFlag(ItemHasContents, true);
    viewer = new osgViewer::Viewer;
    viewer->setUpViewInWindow(0, 0, 800, 600);
    viewer->setSceneData(osgDB::readNodeFile("cow.osgt"));
    viewer->run();
}

void Viewer::setCamera(Camera *camera) {
    if (m_camera == camera)
        return;

    m_camera = camera;
    emit cameraChanged(camera);
}

void Viewer::setScene(Scene *scene) {
    if (m_scene == scene)
        return;

    m_scene = scene;
    emit sceneChanged(scene);
}

QSGNode* Viewer::updatePaintNode(QSGNode* oldNode, QQuickItem::UpdatePaintNodeData*)
{
    QSGSimpleRectNode* n = static_cast<QSGSimpleRectNode*>(oldNode);
    if (!n) {
        n = new QSGSimpleRectNode();
        n->setColor(camera()->color());
    }
    n->setRect(boundingRect());

    return n;
}

