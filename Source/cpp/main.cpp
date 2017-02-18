#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "Base/Core.h"
#include "Base/Settings.h"
#include "Base/Process.h"
#include "Base/FileSystemModel.h"
#include "Base/OperatorModel.h"
#include "Base/OperatorProxyModel.h"
#include "Db/SproutDb.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    app.setApplicationName("Sprout Editor");
    app.setApplicationVersion("0.1.0");

    qmlRegisterType<FileSystemModel>("SproutE", 0, 1, "FileSystemModel");
    qmlRegisterType<SproutDb>("SproutE", 0, 1, "SproutDb");
    qmlRegisterType<Process>("SproutE", 0, 1, "Process");

    Core core;
    Settings settings;

    OperatorModel operatorModel;
    OperatorProxyModel operatorProxyModel;
    operatorProxyModel.setSourceModel(&operatorModel);
    operatorProxyModel.setFilterRole(operatorModel.firstRole());

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("Core", &core);
    engine.rootContext()->setContextProperty("Settings", &settings);
    engine.rootContext()->setContextProperty("OperatorModel", &operatorModel);
    engine.rootContext()->setContextProperty("OperatorProxyModel", &operatorProxyModel);

#ifdef QT_DEBUG
    engine.rootContext()->setContextProperty("debugMode", QVariant(true));
#else
    engine.rootContext()->setContextProperty("debugMode", QVariant(false));
#endif

    engine.load(QUrl("qrc:/qml/Main.qml"));

    if (engine.rootObjects().isEmpty()) return EXIT_FAILURE;

    return app.exec();
}
