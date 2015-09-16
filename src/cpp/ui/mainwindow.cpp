#include "mainwindow.h"
#include "osgwidget.h"
#include "version.h"
#include "../settings.h"
#include <QtCore/QRect>
#include <QApplication>
#include <QDebug>
#include <QScreen>
#include <QGuiApplication>
#include <QMenuBar>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QLineEdit>

extern QSharedPointer<Settings> settings;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("Greenery");
    setMinimumSize(160, 160);

    QMap<QString, int>map = ::settings.data()->getGeometry();
    if (map.isEmpty()) {
        // move window to center screen
        auto *screen = QGuiApplication::primaryScreen();
        auto screenSize = screen->size();
        int width = 800;
        int height = 600;
        int x = (screenSize.width() - width) / 2;
        int y = (screenSize.height() - height) / 2;
        setGeometry(x, y, width, height);
    } else {
        setGeometry(map["x"], map["y"], map["width"], map["height"]);
    }

    OsgWidget* osgWidget = new OsgWidget(this, Qt::Widget, osgViewer::CompositeViewer::SingleThreaded);
    setCentralWidget(osgWidget);

    createActions();
    createMenus();
}

void MainWindow::newFile() {
    qDebug() << "new";
}

void MainWindow::open() {
    qDebug() << "open";
}

void MainWindow::quitApp() {
    close();
}

void MainWindow::about() {
    QMessageBox::about(this, tr("About Greenery"),
            QString("<h3>Greenery %1</h3>Build date: %2<br>Copyright (c) 2015, Vladimir Zarypov").arg(Version::full()).arg(__DATE__));
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
    fileMenu->addSeparator();
    fileMenu->addAction(quitAct);

    helpMenu = menuBar()->addMenu(tr("Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event)
    QMap<QString, int> map;
    map["x"] = x();
    map["y"] = y();
    map["width"] = width();
    map["height"] = height();
    ::settings.data()->setGeometry(map);
}


