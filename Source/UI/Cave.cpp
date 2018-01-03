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
    process->setProgram(QCoreApplication::applicationDirPath() + "/irbis");
    QStringList arguments;
    arguments << m_filePath;
    process->setArguments(arguments);
    connect(process, &QProcess::readyRead, this, &Cave::onReadyRead);
}

Cave::~Cave() {

}

void Cave::build() {
    process->start();
}

void Cave::stop() {
    qDebug() << "Stop build";
}

QString Cave::filePath() const {
    return m_filePath;
}

void Cave::onReadyRead() {
    QTextStream in(process->readAll());
    while (!in.atEnd()) {
        outputMessage(in.readLine());
    }
}
