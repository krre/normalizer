#include "Editor3D.h"
#include <QtWidgets>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DExtras/QForwardRenderer>
#include <QDebug>

Editor3D::Editor3D(const QString& filePath) :
    filePath(filePath),
    sproutManager(new SproutManager(filePath, this)) {
    Qt3DExtras::Qt3DWindow* view = new Qt3DExtras::Qt3DWindow();
    view->defaultFrameGraph()->setClearColor(QColor(QRgb(0x4d4d4f)));
    QWidget* container = QWidget::createWindowContainer(view);
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setMargin(0);
    layout->addWidget(container);
}

Editor3D::~Editor3D() {

}

void Editor3D::load() {

}
