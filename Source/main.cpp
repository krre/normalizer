#include <QCoreApplication>

int main(int argc, char* argv[]) {
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("Sprout Runtime");
    QCoreApplication::setApplicationVersion("0.1.0");

    return app.exec();
}
