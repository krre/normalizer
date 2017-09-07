#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setWindowTitle(QApplication::applicationName());
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_actionExit_triggered(bool checked) {
    Q_UNUSED(checked)
    QApplication::quit();
}
