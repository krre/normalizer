#pragma once

#include <QObject>
#include <QWidget>
#include <QTimer>

#include <osgViewer/CompositeViewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgQt/GraphicsWindowQt>

class OsgWidget : public QWidget, osgViewer::CompositeViewer
{
    Q_OBJECT
public:
    explicit OsgWidget(QWidget* parent = 0, Qt::WindowFlags f = 0, osgViewer::ViewerBase::ThreadingModel threadingModel = osgViewer::CompositeViewer::SingleThreaded);
    void setProjectPath(QString projectPath) { m_projectPath = projectPath; }
    QString projectPath() { return m_projectPath; }

protected:
    QTimer _timer;

private:
    QWidget* addViewWidget(osgQt::GraphicsWindowQt* gw, osg::Node* scene);
    osgQt::GraphicsWindowQt* createGraphicsWindow(int x, int y, int w, int h, const std::string& name="", bool windowDecoration=false);
    virtual void paintEvent(QPaintEvent* event) { Q_UNUSED(event); frame(); }
    QString m_projectPath;
};
