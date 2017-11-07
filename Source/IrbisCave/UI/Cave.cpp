#include "Cave.h"
#include <QtCore>
#include <QtWidgets>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DExtras/QForwardRenderer>

Cave::Cave() {
    Qt3DExtras::Qt3DWindow* view = new Qt3DExtras::Qt3DWindow();
    view->defaultFrameGraph()->setClearColor(QColor(QRgb(0x4d4d4f)));
    QWidget* container = QWidget::createWindowContainer(view);
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setMargin(0);
    layout->addWidget(container);
}

Cave::~Cave() {

}

void Cave::newIrbis(const QString& path) {
    m_filePath = path;
    qDebug() << m_filePath;
}

void Cave::openIrbis(const QString& path) {
    m_filePath = path;
    qDebug() << m_filePath;
}

void Cave::copyIrbis(const QString& path) {
    m_filePath = path;
}

QString Cave::filePath() const {
    return m_filePath;
}
