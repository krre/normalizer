#include "mainwindow.h"
#include <QApplication>
#include <QtCore/QRect>
#include <QDesktopWidget>
#include <QDebug>

#include "osgwidget.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("Greenery");

    // move window to center screen
    QRect desktopSize = QApplication::desktop()->screenGeometry();
    int x = (desktopSize.width() - size().width()) / 2;
    int y = (desktopSize.height() - size().height()) / 2;
    move(x, y);

    OsgWidget* osgWidget = new OsgWidget(this, Qt::Widget, osgViewer::CompositeViewer::SingleThreaded);
    setCentralWidget(osgWidget);
}
