#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "../Defines.h"
#include <QMessageBox>

MainWindow::MainWindow() : ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setWindowTitle(QApplication::applicationName());
    ui->splitter->setSizes({ 100, 500 });
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_actionExit_triggered(bool checked) {
    Q_UNUSED(checked)
    QApplication::quit();
}

void MainWindow::on_actionAbout_triggered(bool checked) {
    Q_UNUSED(checked)
    QMessageBox::about(this, tr("About %1").arg(APP_NAME),
        tr("<h3>%1 %2</h3> \
           Based on Qt %3<br> \
           Build on %4<br><br> \
           <a href=%5>%5</a><br><br> \
           Copyright © 2015-2017, Vladimir Zarypov").
        arg(APP_NAME).arg(APP_VERSION_STR).arg(QT_VERSION_STR).arg(__DATE__).arg(APP_URL));
}
