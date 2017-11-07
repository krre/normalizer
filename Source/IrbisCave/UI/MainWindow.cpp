#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Cave.h"
#include "Core/Defines.h"
#include <QtWidgets>

MainWindow::MainWindow() :
        ui(new Ui::MainWindow),
        m_settings(QCoreApplication::applicationDirPath() + "/" + APP_SETTINGS_NAME, QSettings::IniFormat) {
    ui->setupUi(this);
    m_cave = new Cave;
    setCentralWidget(m_cave);
    removeToolBar(ui->mainToolBar); // TODO: Temporary hide.
    ui->statusBar->hide(); // TODO: Temporaty hide.
    readSettings();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_actionNew_triggered() {
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save Irbis File"), QString(), "Irbis (*.irbis);;All Files(*.*)");
    if (!filePath.isEmpty()) {
        QFileInfo info(filePath);
        if (info.suffix() != "irbis") {
            filePath += ".irbis";
        }
        changeWindowTitle(filePath);
        m_cave->newIrbis(filePath);
    }
}

void MainWindow::on_actionOpen_triggered() {
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open Irbis File"), QString(), "Irbis (*.irbis);;All Files(*.*)");
    if (!filePath.isEmpty()) {
        changeWindowTitle(filePath);
        m_cave->openIrbis(filePath);
    }
}

void MainWindow::on_actionSave_As_triggered() {

}

void MainWindow::on_actionExit_triggered() {
    QApplication::quit();
}

void MainWindow::on_actionAbout_triggered() {
    QMessageBox::about(this, tr("About %1").arg(APP_NAME),
        tr("<h3>%1 %2</h3> \
           Based on Qt %3<br> \
           Build on %4<br><br> \
           <a href=%5>%5</a><br><br> \
           Copyright © 2017, Vladimir Zarypov").
           arg(APP_NAME).arg(APP_VERSION_STR).arg(QT_VERSION_STR).arg(__DATE__).arg(APP_URL));
}

void MainWindow::readSettings() {
    m_settings.beginGroup("MainWindow");
    resize(m_settings.value("size", QSize(1000, 600)).toSize());
    move(m_settings.value("pos", QPoint(200, 200)).toPoint());
    m_settings.endGroup();

    m_settings.beginGroup("Cave");
    QString filePath = m_settings.value("filePath").toString();
    if (!filePath.isEmpty()) {
        changeWindowTitle(filePath);
        m_cave->openIrbis(filePath);
    } else {
        changeWindowTitle();
    }
    m_settings.endGroup();
}

void MainWindow::writeSettings() {
    m_settings.beginGroup("MainWindow");
    m_settings.setValue("size", size());
    m_settings.setValue("pos", pos());
    m_settings.endGroup();

    m_settings.beginGroup("Cave");
    m_settings.setValue("filePath", m_cave->filePath());
    m_settings.endGroup();
}

void MainWindow::changeWindowTitle(const QString& filePath) {
    QString title = QApplication::applicationName();
    if (!filePath.isEmpty()) {
        QFileInfo info(filePath);
        title += " - " + info.fileName();
    }
    setWindowTitle(title);
}

void MainWindow::closeEvent(QCloseEvent* event) {
    writeSettings();
    event->accept();
}
