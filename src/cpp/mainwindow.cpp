#include <QScreen>
#include <QGuiApplication>
#include <QApplication>
#include <QMenuBar>
#include <QMessageBox>
#include <QDebug>
#include <QVBoxLayout>
#include <QLineEdit>
#include "mainwindow.h"

MainWindow::MainWindow() : QMainWindow() {
    setWindowTitle("Greenery");
    setMinimumSize(160, 160);

    auto *screen = QGuiApplication::primaryScreen();
    auto screenSize = screen->size();
    auto width = 800;
    auto height = 600;
    auto x = (screenSize.width() - width) / 2;
    auto y = (screenSize.height() - height) / 2;
    setGeometry(x, y, width, height);
    setCentralWidget(&visualArea);

    createActions();
    createMenus();
    createStatusBar();
}

void MainWindow::newFile() {
    qDebug() << "new";
}

void MainWindow::open() {
    qDebug() << "open";
}

void MainWindow::save() {
    qDebug() << "save";
}

void MainWindow::saveAs() {
    qDebug() << "save as";
}

void MainWindow::quitApp() {
    QApplication::quit();
}

void MainWindow::about() {
    QMessageBox::about(this, tr("About Greenery"),
            tr("<b>Greenery</b>"));
}

void MainWindow::aboutQt() {
    QMessageBox::aboutQt(this);
}

void MainWindow::createActions() {
    newAct = new QAction(tr("New"), this);
    newAct->setShortcut(QKeySequence("Ctrl+N"));
    connect(newAct, SIGNAL(triggered(bool)), this, SLOT(newFile()));

    openAct = new QAction(tr("Open..."), this);
    openAct->setShortcut(QKeySequence("Ctrl+O"));
    connect(openAct, SIGNAL(triggered(bool)), this, SLOT(open()));

    saveAct = new QAction(tr("Save"), this);
    saveAct->setShortcut(QKeySequence("Ctrl+S"));
    connect(saveAct, SIGNAL(triggered(bool)), this, SLOT(save()));

    saveAsAct = new QAction(tr("Save As..."), this);
    saveAsAct->setShortcut(QKeySequence("Ctrl+Shift+S"));
    connect(saveAsAct, SIGNAL(triggered(bool)), this, SLOT(saveAs()));

    quitAct = new QAction(tr("Quit"), this);
    quitAct->setShortcut(QKeySequence("Ctrl+Q"));
    connect(quitAct, SIGNAL(triggered(bool)), this, SLOT(quitApp()));

    aboutAct = new QAction(tr("About..."), this);
    connect(aboutAct, SIGNAL(triggered(bool)), this, SLOT(about()));

    aboutQtAct = new QAction(tr("About Qt..."), this);
    connect(aboutQtAct, SIGNAL(triggered(bool)), this, SLOT(aboutQt()));
}

void MainWindow::createMenus() {
    fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addSeparator();
    fileMenu->addAction(quitAct);

    helpMenu = menuBar()->addMenu(tr("Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}

void MainWindow::createStatusBar() {
    setStatusBar(&statusBar);
}

