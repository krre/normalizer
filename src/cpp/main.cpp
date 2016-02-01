#include <QApplication>
#include <QtQml>
#include "base/core.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("Impression");
    app.setApplicationVersion("0.1.0");

    Core core;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("Core", &core);
    engine.load(QUrl("qrc:/qml/main.qml"));

    return app.exec();
}
