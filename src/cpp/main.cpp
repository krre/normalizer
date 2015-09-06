#include <QApplication>
#include <QtQml>
#include "utils.h"
#include "settings.h"
#include "console.h"
#include "sproutdb.h"
#include "sproutc.h"
#include "project.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<Console>("Greenery.Lib", 1, 0, "Console");
    qmlRegisterType<SproutDb>("Greenery.Lib", 1, 0, "SproutDb");
    qmlRegisterType<SproutC>("Greenery.Lib", 1, 0, "SproutC");

    Utils utils;
    Settings settings;
    Project project;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("PROJECT", &project);
    engine.rootContext()->setContextProperty("UTILS", &utils);
    engine.rootContext()->setContextProperty("SETTINGS", &settings);
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    return app.exec();
}
