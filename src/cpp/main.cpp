#include <QApplication>
#include <QtDebug>
#include <QtQml>
#include <sprout/project.h>
#include <registerosgtypes.h>
#include "version.h"
#include "settings.h"
#include "utils.h"
#include "registertypes.h"

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
        {{"t", "threaded"}, QCoreApplication::translate("main", "Threaded QSG render loop")},
    });

    parser.process(app);

    if (parser.isSet("threaded")) {
        qputenv("QSG_RENDER_LOOP", "threaded");
    } else {
        qputenv("QSG_RENDER_LOOP", "basic");
    }

    QQmlApplicationEngine engine;

    registerTypes();
    registerOsgTypes();

    Utils utils;
    Project project;
    Version version;
    Settings settings;

#ifdef QT_DEBUG
    engine.rootContext()->setContextProperty("isDebug", true);
#else
    engine.rootContext()->setContextProperty("isDebug", false);
#endif

    engine.rootContext()->setContextProperty("PROJECT", &project);
    engine.rootContext()->setContextProperty("UTILS", &utils);
    engine.rootContext()->setContextProperty("Settings", &settings);
    engine.rootContext()->setContextProperty("VERSION", &version);

    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    return app.exec();
}
