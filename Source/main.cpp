#include "UI/SelectWorkspace.h"
#include "UI/MainWindow.h"
#include "Core/Defines.h"
#include "Core/Settings.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setApplicationName(APP_NAME);
    app.setApplicationVersion(APP_VERSION_STR);

    new Settings(QCoreApplication::applicationDirPath() + "/" + APP_SETTINGS_NAME, QSettings::IniFormat);

    if (Settings::instance()->value("Path/workspace").toString().isEmpty()) {
        SelectWorkspace selectWorkspace;
        selectWorkspace.exec();
        if (selectWorkspace.isRejected()) {
            Settings::release();
            return EXIT_SUCCESS;
        }
    }

    MainWindow mainWindow;
    mainWindow.show();

    int errCode = app.exec();

    Settings::release();

    return errCode;
}
