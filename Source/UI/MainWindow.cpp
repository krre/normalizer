#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow) {
    _ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete _ui;
}

void MainWindow::on_actionExit_triggered() {
    QApplication::quit();
}
