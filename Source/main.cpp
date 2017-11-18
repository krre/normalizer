#include <QApplication>
#include "UI/MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setApplicationName("Irbis UnitBuilder");
    app.setApplicationVersion("0.1.0");

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
