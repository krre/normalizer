#include "MainWindow.h"
#include "core/Constants.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setWindowTitle("Normalizer");
    createActions();
    resize(800, 600);
}

MainWindow::~MainWindow() {
}

void MainWindow::onNew() {

}

void MainWindow::onOpen() {

}

void MainWindow::onQuit() {
    writeSettings();
    QCoreApplication::quit();
}

void MainWindow::onAbout() {
    using namespace Const::App;

    QMessageBox::about(this, tr("About %1").arg(Name),
        tr("<h3>%1 %2 %3</h3>\
           IDE for Norm language<br><br> \
           Based on Qt %4<br> \
           Build on %5 %6<br><br> \
           <a href=%7>%7</a><br><br>Copyright © %8, Vladimir Zarypov")
            .arg(Name, Version, Status, QT_VERSION_STR, BuildDate, BuildTime, Url, CopyrightYear));
}

void MainWindow::createActions() {
    QMenu* fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(tr("New..."), this, &MainWindow::onNew, QKeySequence("Ctrl+N"));
    fileMenu->addAction(tr("Open..."), this, &MainWindow::onOpen, QKeySequence("Ctrl+O"));
    fileMenu->addSeparator();
    fileMenu->addAction(tr("Exit"), this, &MainWindow::onQuit, QKeySequence("Ctrl+Q"));

    QMenu* helpMenu = menuBar()->addMenu(tr("Help"));
    helpMenu->addAction(tr("About %1...").arg(Const::App::Name), this, &MainWindow::onAbout);
}

void MainWindow::readSettings() {

}

void MainWindow::writeSettings() {

}
