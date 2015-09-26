#include "view.h"

View::View()
{
    view = new osgViewer::View;
    camera = view->getCamera();

    osg::GraphicsContext::Traits* traits = new osg::GraphicsContext::Traits;
    osg::DisplaySettings* ds = osg::DisplaySettings::instance().get();
    traits->doubleBuffer = true;
    traits->alpha = ds->getMinimumNumAlphaBits();
    traits->stencil = ds->getMinimumNumStencilBits();
    traits->sampleBuffers = ds->getMultiSamples();
    traits->samples = ds->getNumMultiSamples();

    graphicsContext = osg::GraphicsContext::createGraphicsContext(traits);
    camera->setGraphicsContext(graphicsContext);
    camera->setClearColor(osg::Vec4(0.2, 0.2, 0.6, 1.0));
    setFlag(QQuickItem::ItemHasContents, true);
}

void View::geometryChanged(const QRectF& newGeometry, const QRectF& oldGeometry)
{
    int width = newGeometry.width();
    int height = newGeometry.height();
    if (width > 0 && height > 0) {
        camera->setViewport(0, 0, width, height);
        camera->setProjectionMatrixAsPerspective(30.0f, static_cast<double>(width) / static_cast<double>(height), 1.0f, 10000.0f );
        graphicsContext->resized(0, 0, width, height);
        qDebug() << oldGeometry << newGeometry;
        update();
    }
}

QSGNode* View::updatePaintNode(QSGNode* oldNode, QQuickItem::UpdatePaintNodeData*)
{
    qDebug() << "updatePaintNode" << oldNode;
    return oldNode;
}

