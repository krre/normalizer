#include <QtGui/QGuiApplication>
#include <QtQml>
#include "utils.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    Utils utils;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("UTILS", &utils);
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    return app.exec();
}
