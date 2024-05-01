#include "core/Application.h"
#include "external/settings/FileSettings.h"
#include "external/network/http/HttpRestApi.h"
#include "qml/QmlTypes.h"
#include "qml/QmlController.h"
#include <QQmlContext>
#include <QQmlApplicationEngine>

int main(int argc, char* argv[]) {
    Application app(argc, argv);

    FileSettings fileSettings;
    HttpRestApi httpRestApi(fileSettings.developmentServer().url);

    Qml::QmlController::setRestApi(&httpRestApi);
    Qml::QmlTypes::registerTypes();

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("app", &app);
    engine.load(QUrl("qrc:/qml/Main.qml"));

    if (engine.rootObjects().isEmpty()) {
        return EXIT_FAILURE;
    }

    return app.exec();
}
