#include "UI/SelectWorkspace.h"
#include "UI/MainWindow.h"
#include "Core/Defines.h"
#include "Core/Settings.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setApplicationName(APP_NAME);
    app.setApplicationVersion(APP_VERSION_STR);

    new IrbisCave::Settings(QCoreApplication::applicationDirPath() + "/" + APP_SETTINGS_NAME, QSettings::IniFormat);

    if (IrbisCave::Settings::instance()->value("Path/workspace").toString().isEmpty()) {
        IrbisCave::SelectWorkspace selectWorkspace;
        selectWorkspace.exec();
        if (selectWorkspace.getIsRejected()) {
            IrbisCave::Settings::release();
            return EXIT_SUCCESS;
        }
    }

    IrbisCave::MainWindow mainWindow;
    mainWindow.show();

    int errCode = app.exec();

    IrbisCave::Settings::release();

    return errCode;
}
