#include "MainWindow.h"
#include "core/Constants.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setWindowTitle(Const::App::Name);
    resize(800, 600);
}

MainWindow::~MainWindow() {
}
