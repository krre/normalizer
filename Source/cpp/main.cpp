#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QCommandLineParser>
#include <QDebug>
#include "Base/Settings.h"
#include "Base/Core.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    QApplication::setApplicationName("Sprout Runtime");
    QApplication::setApplicationVersion("0.1.0");

    QCommandLineParser parser;
    parser.setApplicationDescription("Sprout virtual machine");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("source", QCoreApplication::translate("main", "Source file to run"));
    parser.process(app);

    QString sourceFilePath;

    if (argc != 1) {
        const QStringList args = parser.positionalArguments();
        if (args.count() == 0) {
            qDebug() << "Unknown source file";
            parser.showHelp();
        } else {
            sourceFilePath = args.at(0);
        }
    }

    Core core;
    Settings settings;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("Core", &core);
    engine.rootContext()->setContextProperty("Settings", &settings);
    engine.rootContext()->setContextProperty("SourceFile", sourceFilePath);

#ifdef QT_DEBUG
    engine.rootContext()->setContextProperty("debugMode", QVariant(true));
#else
    engine.rootContext()->setContextProperty("debugMode", QVariant(false));
#endif

    engine.load(QUrl("qrc:/qml/Main.qml"));

    if (engine.rootObjects().isEmpty()) return EXIT_FAILURE;

    return app.exec();
}
