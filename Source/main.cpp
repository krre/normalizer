#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setApplicationName("Irbis Builder");
    app.setApplicationVersion("0.1.0");

    return app.exec();
}
