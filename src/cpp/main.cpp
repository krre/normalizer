#include <QApplication>
#include <QtQml>
#include "base/core.h"
#include "base/settings.h"
#include "base/projectfilesystemmodel.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("Impression");
    app.setApplicationVersion("0.1.0");

    Core core;
    Settings settings;

    QQmlApplicationEngine engine;
    qmlRegisterUncreatableType<ProjectFileSystemModel>("Impression", 1, 0, "ProjectFileSystemModel", "Cannot create a FileSystemModel instance.");
    QFileSystemModel* fsm = new ProjectFileSystemModel(&engine);
    engine.rootContext()->setContextProperty("fileSystemModel", fsm);
    engine.rootContext()->setContextProperty("rootPathIndex", fsm->index(fsm->rootPath()));
    engine.rootContext()->setContextProperty("Core", &core);
    engine.rootContext()->setContextProperty("Settings", &settings);
    engine.load(QUrl("qrc:/qml/main.qml"));

    if (engine.rootObjects().isEmpty()) return -1;

    return app.exec();
}
