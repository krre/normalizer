#include "UI/MainWindow.h"
#include "Core/Defines.h"
#include "Core/Settings.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setApplicationName(APP_NAME);
    app.setApplicationVersion(APP_VERSION_STR);

    new Settings;

    MainWindow mainWindow;
    mainWindow.show();

    int errCode = app.exec();

    Settings::release();

    return errCode;
}
