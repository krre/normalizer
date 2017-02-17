#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "Base/Settings.h"
#include "Base/Core.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    QApplication::setApplicationName("Sprout Runtime");
    QApplication::setApplicationVersion("0.1.0");

    Core core;
    Settings settings;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("Core", &core);
    engine.rootContext()->setContextProperty("Settings", &settings);

#ifdef QT_DEBUG
    engine.rootContext()->setContextProperty("debugMode", QVariant(true));
#else
    engine.rootContext()->setContextProperty("debugMode", QVariant(false));
#endif

    engine.load(QUrl("qrc:/qml/Main.qml"));

    if (engine.rootObjects().isEmpty()) return EXIT_FAILURE;

    return app.exec();
}
