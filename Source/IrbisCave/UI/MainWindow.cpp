#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Core/Defines.h"

MainWindow::MainWindow() :
        ui(new Ui::MainWindow),
        settings(QCoreApplication::applicationDirPath() + "/" + APP_SETTINGS_NAME, QSettings::IniFormat) {
    ui->setupUi(this);
    setWindowTitle(QApplication::applicationName());
    readSettings();
}

MainWindow::~MainWindow() {
    writeSettings();
    delete ui;
}

void MainWindow::readSettings() {
    settings.beginGroup("MainWindow");
    resize(settings.value("size", QSize(1000, 600)).toSize());
    move(settings.value("pos", QPoint(200, 200)).toPoint());
    settings.endGroup();
}

void MainWindow::writeSettings() {
    settings.beginGroup("MainWindow");
    settings.setValue("size", size());
    settings.setValue("pos", pos());
    settings.endGroup();
}
