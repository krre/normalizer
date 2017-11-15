#include "Cave.h"
#include "Db/DatabaseManager.h"
#include <QtCore>
#include <QtWidgets>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DExtras/QForwardRenderer>

Cave::Cave(const QString& filePath) : _filePath(filePath) {
    Qt3DExtras::Qt3DWindow* view = new Qt3DExtras::Qt3DWindow();
    view->defaultFrameGraph()->setClearColor(QColor(QRgb(0x4d4d4f)));
    QWidget* container = QWidget::createWindowContainer(view);
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setMargin(0);
    layout->addWidget(container);

    _databaseManager = new DatabaseManager(filePath, this);
}

Cave::~Cave() {

}

void Cave::newIrbis(const QString& path) {
    _filePath = path;
    qDebug() << "New Irbis:" << _filePath;
}

void Cave::openIrbis(const QString& path) {
    _filePath = path;
    qDebug() << "Open Irbis:" << _filePath;
}

void Cave::copyIrbis(const QString& path) {
    _filePath = path;
    qDebug() << "Copy Irbis:" << _filePath;
}

void Cave::closeIrbis() {
    qDebug() << "Close Irbis:" << _filePath;
    _filePath = "";
}

QString Cave::filePath() const {
    return _filePath;
}
