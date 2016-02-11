#include <QApplication>
#include <QtQml>
#include "base/core.h"
#include "base/settings.h"
#include "base/filesystemmodel.h"
#include "base/operatormodel.h"
#include "base/operatorproxymodel.h"
#include "db/sproutdb.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("Usilage");
    app.setApplicationVersion("0.1.0");

    qmlRegisterType<FileSystemModel>("Usilage", 1, 0, "FileSystemModel");
    qmlRegisterType<SproutDb>("Usilage", 1, 0, "SproutDb");

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
    engine.rootContext()->setContextProperty("isDebug", QVariant(true));
#else
    engine.rootContext()->setContextProperty("isDebug", QVariant(false));
#endif

    engine.load(QUrl("qrc:/qml/main.qml"));

    if (engine.rootObjects().isEmpty()) return EXIT_FAILURE;

    return app.exec();
}
