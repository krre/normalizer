#include "osgwidget.h"

OsgWidget::OsgWidget(QWidget* parent, Qt::WindowFlags f, osgViewer::ViewerBase::ThreadingModel threadingModel) : QWidget(parent, f)
{
    setThreadingModel(threadingModel);
}

