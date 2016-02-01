#include <QApplication>
#include <QtQml>
#include "base/core.h"
#include "base/settings.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("Impression");
    app.setApplicationVersion("0.1.0");

    Core core;
    Settings settings;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("Core", &core);
    engine.rootContext()->setContextProperty("Settings", &settings);
    engine.load(QUrl("qrc:/qml/main.qml"));

    return app.exec();
}
