#include "Cave.h"
#include "Db/DatabaseManager.h"
#include <QtCore>
#include <QtWidgets>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DExtras/QForwardRenderer>

Cave::Cave(const QString& filePath) : m_filePath(filePath) {
    Qt3DExtras::Qt3DWindow* view = new Qt3DExtras::Qt3DWindow();
    view->defaultFrameGraph()->setClearColor(QColor(QRgb(0x4d4d4f)));
    QWidget* container = QWidget::createWindowContainer(view);
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setMargin(0);
    layout->addWidget(container);

    databaseManager = new DatabaseManager(filePath, this);
    process = new QProcess(this);
}

Cave::~Cave() {

}

void Cave::build() {
    process->startDetached("irbis");
}

void Cave::stop() {
    qDebug() << "Stop build";
}

QString Cave::filePath() const {
    return m_filePath;
}
