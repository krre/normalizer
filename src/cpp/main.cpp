#include <QApplication>
#include <QtQml>
#include "utils.h"
#include "settings.h"
#include "interpreter.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<Interpreter>("Greenery.Lib", 1, 0, "Interpreter");

    Utils utils;
    Settings settings;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("UTILS", &utils);
    engine.rootContext()->setContextProperty("SETTINGS", &settings);
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    return app.exec();
}
