#include <QApplication>
#include <QtDebug>
#include <QtQml>
#include "version.h"
#include "settings.h"
#include "utils.h"
#include "registertypes.h"
#include <sprout/project.h>

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
        {{"t", "threaded"}, QCoreApplication::translate("main", "Threaded QSG render loop")},
    });

    parser.process(app);

    bool isThreaded = parser.isSet("threaded");
    if (isThreaded) {
        qputenv("QSG_RENDER_LOOP", "threaded");
    } else {
        qputenv("QSG_RENDER_LOOP", "basic");
    }

    ::settings = QSharedPointer<Settings>(new Settings());
    QQmlApplicationEngine engine;

    registerTypes();

    Utils utils;
    Project project;
    Version version;

    engine.rootContext()->setContextProperty("PROJECT", &project);
    engine.rootContext()->setContextProperty("UTILS", &utils);
    engine.rootContext()->setContextProperty("SETTINGS", ::settings.data());
    engine.rootContext()->setContextProperty("VERSION", &version);
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    return app.exec();
}
