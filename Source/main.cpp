#include <QApplication>
#include "UI/MainWindow.h"
#include "Core/Defines.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setApplicationName(APP_NAME);
    app.setApplicationVersion(APP_VERSION_STR);

    QString filePath;
    if (argc > 1) {
        filePath = QString(argv[1]);
    }

    MainWindow mainWindow(filePath);
    mainWindow.show();

    return app.exec();
}
