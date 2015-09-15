#include <QApplication>
#include <QtQml>
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
        {{"p", "plane"}, QCoreApplication::translate("main", "Plain mode")},
    });

    parser.process(app);

//    bool isPlain = parser.isSet("plane");
//    qDebug() << isPlain;

    qmlRegisterType<Console>("Greenery.Lib", 1, 0, "Console");
    qmlRegisterType<SproutDb>("Greenery.Lib", 1, 0, "SproutDb");

    Utils utils;
    Settings settings;
    Project project;
    Version version;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("PROJECT", &project);
    engine.rootContext()->setContextProperty("UTILS", &utils);
    engine.rootContext()->setContextProperty("SETTINGS", &settings);
    engine.rootContext()->setContextProperty("VERSION", &version);
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    return app.exec();
}
