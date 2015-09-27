#include <QApplication>
#include <QtDebug>
#include <QtQml>
#include <sprout/project.h>
#include "version.h"
#include "settings.h"
#include "utils.h"
#include "registertypes.h"
#include "osg-adapter/osgViewer/viewer.h"

QSharedPointer<Settings> settings;

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    app.setApplicationName("Greenery");
    QCoreApplication::setApplicationVersion(Version::full());

    QCommandLineParser parser;
    parser.setApplicationDescription("IDE for Sprout language");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("source", QCoreApplication::translate("main", "Sprout file to edit"));

    parser.addOptions({
        {{"t", "threaded"}, QCoreApplication::translate("main", "Threaded QSG render loop")},
    });

    parser.process(app);

    bool isThreaded = parser.isSet("threaded");
    if (isThreaded) {
        qputenv("QSG_RENDER_LOOP", "threaded");
    } else {
        qputenv("QSG_RENDER_LOOP", "basic");
    }

    int exitCode = 0;
    {
        QQmlApplicationEngine engine;

        registerTypes();

        Utils utils;
        Project project;
        Version version;
        ::settings = QSharedPointer<Settings>(new Settings());

        engine.rootContext()->setContextProperty("PROJECT", &project);
        engine.rootContext()->setContextProperty("UTILS", &utils);
        engine.rootContext()->setContextProperty("SETTINGS", ::settings.data());
        engine.rootContext()->setContextProperty("VERSION", &version);
        engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

        exitCode = app.exec();
    }

    // As the render threads make use of our QGuiApplication object
    // to clean up gracefully, wait for them to finish before
    // QGuiApp is taken off the heap.
    foreach (QThread *t, Viewer::threads) {
        t->wait();
        delete t;
    }

    return exitCode;
}
