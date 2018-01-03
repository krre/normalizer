#include <QApplication>
#include "UI/MainWindow.h"
#include "Core/Defines.h"
#include "Core/Settings.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setApplicationName(APP_NAME);
    app.setApplicationVersion(APP_VERSION_STR);

    new IrbisUnitBuilder::Settings(QCoreApplication::applicationDirPath() + "/" + APP_SETTINGS_NAME, QSettings::IniFormat);

    QString filePath;
    if (argc > 1) {
        filePath = QString(argv[1]);
    }

    IrbisUnitBuilder::MainWindow mainWindow(filePath);
    mainWindow.show();

    int errCode = app.exec();

    IrbisUnitBuilder::Settings::release();

    return errCode;
}
