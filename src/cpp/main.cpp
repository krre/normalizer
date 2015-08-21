#include <QApplication>
#include <QtQml>
#include "Utils.h"
#include "Settings.h"
#include "Interpreter.h"
#include "SproutDb.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<Interpreter>("Greenery.Lib", 1, 0, "Interpreter");
    qmlRegisterType<SproutDb>("Greenery.Lib", 1, 0, "SproutDb");

    Utils utils;
    Settings settings;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("UTILS", &utils);
    engine.rootContext()->setContextProperty("SETTINGS", &settings);
    engine.load(QUrl(QStringLiteral("qrc:/qml/Main.qml")));

    return app.exec();
}
