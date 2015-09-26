#include <QApplication>
#include <QtDebug>
#include <QtQml>
#include "version.h"
#include "settings.h"
#include "utils.h"
#include "console.h"
#include <sprout/sproutdb.h>
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

    qmlRegisterType<Console>("Greenery", 0, 1, "Console");
    qmlRegisterType<SproutDb>("Greenery", 0, 1, "SproutDb");

    Utils utils;
    Project project;
    Version version;

    QString osgQtQuickPath = qgetenv("OSGQTQUICK_HOME");
    if (osgQtQuickPath.isEmpty()) {
        osgQtQuickPath = ".";
    }
    engine.addImportPath(osgQtQuickPath + "/imports");
    engine.rootContext()->setContextProperty("PROJECT", &project);
    engine.rootContext()->setContextProperty("UTILS", &utils);
    engine.rootContext()->setContextProperty("SETTINGS", ::settings.data());
    engine.rootContext()->setContextProperty("VERSION", &version);
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    return app.exec();
}
