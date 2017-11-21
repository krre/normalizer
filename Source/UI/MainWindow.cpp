#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Editor3D.h"
#include "Core/Defines.h"
#include "Core/Settings.h"
#include <QtWidgets>

MainWindow::MainWindow(const QString& filePath) :
        _filePath(filePath),
        _ui(new Ui::MainWindow) {
    _settings = Settings::instance();

    _ui->setupUi(this);

    readSettings();

    if (!filePath.isEmpty()) {
        openFile(filePath);
    }
}

MainWindow::~MainWindow() {
    delete _ui;
}

void MainWindow::closeEvent(QCloseEvent* event) {
    writeSettings();
    event->accept();
}

void MainWindow::on_actionOpen_triggered() {
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open Irbis File"), QString(), "Irbis (*.irbis);;All Files(*.*)");
    if (!filePath.isEmpty()) {
        openFile(filePath);
    }
}

void MainWindow::on_actionClose_triggered() {
    closeFile();
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
    _settings->beginGroup("MainWindow");
    resize(_settings->value("size", QSize(800, 600)).toSize());
    move(_settings->value("pos", QPoint(200, 200)).toPoint());
    _settings->endGroup();
}

void MainWindow::writeSettings() {
    _settings->beginGroup("MainWindow");
    _settings->setValue("size", size());
    _settings->setValue("pos", pos());
    _settings->endGroup();
}

void MainWindow::openFile(const QString& filePath) {
    closeFile();
    _filePath = filePath;
    editor3d.reset(new Editor3D(filePath));
    setCentralWidget(editor3d.data());
    changeWindowTitle(filePath);
}

void MainWindow::closeFile() {
    _filePath = QString();
    editor3d.reset();
    changeWindowTitle();
}

void MainWindow::changeWindowTitle(const QString& filePath) {
    QString title = QApplication::applicationName();
    if (!filePath.isEmpty()) {
        QFileInfo info(filePath);
        title = info.fileName() + " - " + title;
    }
    setWindowTitle(title);
}
