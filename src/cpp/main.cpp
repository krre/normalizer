#include <QApplication>
#include <QtDebug>
//#include <QtQml>
#include "ui/mainwindow.h"
#include "utils.h"
#include "settings.h"
#include "console.h"
#include "sproutdb.h"
#include "sproutc.h"
#include "project.h"
#include "version.h"

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

    bool isQml = parser.isSet("qml");

    if (isQml) {
//        qmlRegisterType<Console>("Greenery.Lib", 1, 0, "Console");
//        qmlRegisterType<SproutDb>("Greenery.Lib", 1, 0, "SproutDb");

//        Utils* utils = new Utils();
//        Settings* settings = new Settings();
//        Project* project = new Project();
//        Version* version = new Version();

//        QQmlApplicationEngine* engine = new QQmlApplicationEngine();
//        engine->rootContext()->setContextProperty("PROJECT", project);
//        engine->rootContext()->setContextProperty("UTILS", utils);
//        engine->rootContext()->setContextProperty("SETTINGS", settings);
//        engine->rootContext()->setContextProperty("VERSION", version);
//        engine->load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    } else {
        MainWindow* mainWindow = new MainWindow();
        mainWindow->resize(800, 600);
        mainWindow->show();
    }

    return app.exec();
}
