#pragma once

#include <QObject>
#include <QWidget>

#include <osgViewer/CompositeViewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgQt/GraphicsWindowQt>

class OsgWidget : public QWidget, osgViewer::CompositeViewer
{
    Q_OBJECT
public:
    explicit OsgWidget(QWidget* parent = 0, Qt::WindowFlags f = 0, osgViewer::ViewerBase::ThreadingModel threadingModel = osgViewer::CompositeViewer::SingleThreaded);

signals:

public slots:
};
