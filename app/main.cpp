#include "core/Application.h"
#include <QQmlContext>
#include <QQmlApplicationEngine>

int main(int argc, char* argv[]) {
    Application app(argc, argv);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("app", &app);
    engine.load(QUrl("qrc:/qml/Main.qml"));

    if (engine.rootObjects().isEmpty()) {
        return EXIT_FAILURE;
    }

    return app.exec();
}
