#include <osgDB/ReadFile>
#include <osgGA/MultiTouchTrackballManipulator>
#include "workarea.h"

WorkArea::WorkArea(QWidget* parent, Qt::WindowFlags f, osgViewer::ViewerBase::ThreadingModel threadingModel) : QWidget(parent, f) {
    setThreadingModel(threadingModel);

    // disable the default setting of viewer.done() by pressing Escape.
    setKeyEventSetsDone(0);

    QWidget* widget = addViewWidget(createGraphicsWindow(0, 0, width(), height()), osgDB::readNodeFile("cow.osgt"));
    QBoxLayout* layout = new QBoxLayout(QBoxLayout::TopToBottom);
    layout->setContentsMargins(1, 1, 1, 1);
    layout->addWidget(widget);
    setLayout(layout);

    connect(&_timer, SIGNAL(timeout()), this, SLOT(update()));
    _timer.start(10);
}

QWidget* WorkArea::addViewWidget(osgQt::GraphicsWindowQt* gw, osg::Node* scene) {
    osgViewer::View* view = new osgViewer::View;
    addView(view);

    osg::Camera* camera = view->getCamera();
    camera->setGraphicsContext(gw);

    const osg::GraphicsContext::Traits* traits = gw->getTraits();

    camera->setClearColor(osg::Vec4(0.19, 0.12, 0.08, 1));
    camera->setViewport(new osg::Viewport(0, 0, traits->width, traits->height));
    camera->setProjectionMatrixAsPerspective(30.0f, static_cast<double>(traits->width)/static_cast<double>(traits->height), 1.0f, 10000.0f);

    view->setSceneData(scene);
    view->addEventHandler(new osgViewer::StatsHandler);
    osgGA::MultiTouchTrackballManipulator* manipulator = new osgGA::MultiTouchTrackballManipulator;
    manipulator->setWheelZoomFactor(-0.1);
    view->setCameraManipulator(manipulator);
//    gw->setTouchEventsEnabled(true);
    return gw->getGLWidget();
}

osgQt::GraphicsWindowQt* WorkArea::createGraphicsWindow(int x, int y, int w, int h, const std::string& name, bool windowDecoration) {
    osg::DisplaySettings* ds = osg::DisplaySettings::instance().get();
    osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
    traits->windowName = name;
    traits->windowDecoration = windowDecoration;
    traits->x = x;
    traits->y = y;
    traits->width = w;
    traits->height = h;
    traits->doubleBuffer = true;
    traits->alpha = ds->getMinimumNumAlphaBits();
    traits->stencil = ds->getMinimumNumStencilBits();
    traits->sampleBuffers = ds->getMultiSamples();
    traits->samples = ds->getNumMultiSamples();

    return new osgQt::GraphicsWindowQt(traits.get());
}
