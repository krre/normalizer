#include "UI/MainWindow.h"
#include "Core/Defines.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setApplicationName(APP_NAME);
    app.setApplicationVersion(APP_VERSION_STR);

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
