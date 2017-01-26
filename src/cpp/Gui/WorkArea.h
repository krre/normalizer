#pragma once
#include <osgViewer/CompositeViewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgQt/GraphicsWindowQt>

class WorkArea : public QWidget, osgViewer::CompositeViewer {
    Q_OBJECT
public:
    explicit WorkArea(QWidget* parent = 0, Qt::WindowFlags f = 0, osgViewer::ViewerBase::ThreadingModel threadingModel = osgViewer::CompositeViewer::SingleThreaded);

protected:
    void timerEvent(QTimerEvent*) override { update(); }

private:
    QWidget* addViewWidget(osgQt::GraphicsWindowQt* gw, osg::Node* scene);
    osgQt::GraphicsWindowQt* createGraphicsWindow(int x, int y, int w, int h, const std::string& name="", bool windowDecoration=false);
    virtual void paintEvent(QPaintEvent*) override { frame(); }
};
