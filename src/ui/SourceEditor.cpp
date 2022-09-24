#include "SourceEditor.h"
#include "core/Constants.h"
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DExtras/QForwardRenderer>
#include <QtWidgets>

SourceEditor::SourceEditor(QWidget* parent) : QWidget(parent) {
    Qt3DExtras::Qt3DWindow* view = new Qt3DExtras::Qt3DWindow;
    view->defaultFrameGraph()->setClearColor(QColor(QRgb(Const::Window::BackgroundColor)));
    QWidget* container = QWidget::createWindowContainer(view);

    QHBoxLayout* layout = new QHBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(container);

    setLayout(layout);
}
