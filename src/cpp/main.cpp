#include <QApplication>
#include <QtDebug>
#include <QtQml>
#include "version.h"
#include "settings.h"
#include "utils.h"
#include "project.h"
#include "registers.h"

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
    bool isQml = parser.isSet("qml");
    if (isQml) {}

    ::settings = QSharedPointer<Settings>(new Settings());
    QQmlApplicationEngine engine;

    Utils utils;
    Project project;
    Version version;

    registerQmlModules();

    engine.rootContext()->setContextProperty("PROJECT", &project);
    engine.rootContext()->setContextProperty("UTILS", &utils);
    engine.rootContext()->setContextProperty("SETTINGS", ::settings.data());
    engine.rootContext()->setContextProperty("VERSION", &version);
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    return app.exec();
}
