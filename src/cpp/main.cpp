#include <QApplication>
#include <osg/ArgumentParser>
#include <QtDebug>
#include "mainwindow.h"

int main(int argc, char** argv)
{
    osg::ArgumentParser argumentParser(&argc, argv);
    qDebug() << *argumentParser.argv();
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.resize(800, 600);
    mainWindow.show();
    return app.exec();
}
