#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QMessageBox>

MainWindow::MainWindow() : ui(new Ui::MainWindow) {
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

void MainWindow::on_actionAbout_triggered(bool checked) {
    Q_UNUSED(checked)
    QMessageBox::about(this, tr("About %1").arg(QApplication::applicationName()),
        tr("<h3>%1 %2</h3> \
           Based on Qt %3<br> \
           Build on %4<br><br> \
           <a href=\"https://github.com/krre/sprout-editor\"> \
           https://github.com/krre/sprout-editor</a><br><br> \
           Copyright © 2015-2017, Vladimir Zarypov").
        arg(QApplication::applicationName()).arg(QApplication::applicationVersion()).arg(QT_VERSION_STR).arg(__DATE__));
}
