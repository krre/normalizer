#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QCommandLineParser>
#include <QDebug>
#include "Base/Core.h"
#include "Base/Settings.h"
#include "Base/Process.h"
#include "Base/FileSystemModel.h"
#include "Base/OperatorModel.h"
#include "Base/OperatorProxyModel.h"
#include "Db/SproutDb.h"
#include "UI/MainWindow.h"
#include "Defines.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    app.setApplicationName(APP_NAME);
    app.setApplicationVersion(APP_VERSION_STR);

    QCommandLineParser parser;
    parser.addOptions({
        {{"q", "qml"}, QCoreApplication::translate("main", "QML mode")},
    });
    parser.process(app);
    bool isQmlMode = parser.isSet("qml");

    if (isQmlMode) {
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
    } else {
        MainWindow mainWindow;
        mainWindow.show();
        return app.exec();
    }
}
