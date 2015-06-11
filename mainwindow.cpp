#include "QtCore"
#include <QScreen>
#include <QGuiApplication>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Greenery");

    QScreen *screen = QGuiApplication::primaryScreen();
    QSize screenSize = screen->size();
    int width = 800;
    int height = 600;
    int x = (screenSize.width() - width) / 2;
    int y = (screenSize.height() - height) / 2;
    setGeometry(x, y, width, height);
}

