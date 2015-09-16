#include <QApplication>
#include <QtDebug>
#include "ui/mainwindow.h"
#include "version.h"
#include "settings.h"

QSharedPointer<Settings> settings;

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    app.setApplicationName("Greenery");
    QCoreApplication::setApplicationVersion(Version::full());

    QCommandLineParser parser;
    parser.setApplicationDescription("IDE for Sprout language");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("source", QCoreApplication::translate("main", "Sprout file to edit"));

    parser.addOptions({
        {{"q", "qml"}, QCoreApplication::translate("main", "QML Window")},
    });

    parser.process(app);

    ::settings = QSharedPointer<Settings>(new Settings());

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
