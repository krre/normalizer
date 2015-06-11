#include <QScreen>
#include <QGuiApplication>
#include <QApplication>
#include <QMenuBar>
#include <QDebug>
#include "mainwindow.h"

MainWindow::MainWindow() : QMainWindow() {
    QScreen *screen = QGuiApplication::primaryScreen();
    QSize screenSize = screen->size();
    int width = 800;
    int height = 600;
    int x = (screenSize.width() - width) / 2;
    int y = (screenSize.height() - height) / 2;
    setGeometry(x, y, width, height);

    createActions();
    createMenus();

    setWindowTitle("Greenery");
    setMinimumSize(160, 160);
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

void MainWindow::quitApp() {
    QApplication::quit();
}

void MainWindow::about() {
    qDebug() << "about";
}

void MainWindow::aboutQt() {
    qDebug() << "about Qt";
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
    fileMenu->addSeparator();
    fileMenu->addAction(quitAct);

    helpMenu = menuBar()->addMenu(tr("Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}

