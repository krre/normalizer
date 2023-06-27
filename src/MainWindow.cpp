#include "MainWindow.h"
#include "core/Constants.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setWindowTitle(Const::App::Name);
    readSettings();
}

MainWindow::~MainWindow() {
}

void MainWindow::closeEvent(QCloseEvent* event) {
    writeSettings();
    event->accept();
}

void MainWindow::readSettings() {
    QSettings settings;

    if (settings.contains("geometry")) {
        restoreGeometry(settings.value("geometry").toByteArray());
        restoreState(settings.value("state").toByteArray());
    } else {
        const QRect availableGeometry = QGuiApplication::screens().constFirst()->availableGeometry();
        constexpr auto scale = 0.8;
        resize(availableGeometry.width() * scale, availableGeometry.height() * scale);
        move((availableGeometry.width() - width()) / 2, (availableGeometry.height() - height()) / 2);
    }
}

void MainWindow::writeSettings() {
    QSettings settings;
    settings.setValue("geometry", saveGeometry());
    settings.setValue("state", saveState());
}
