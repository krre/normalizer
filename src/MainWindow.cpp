#include "MainWindow.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setWindowTitle("Normalizer");
    resize(800, 600);
}

MainWindow::~MainWindow() {
}
