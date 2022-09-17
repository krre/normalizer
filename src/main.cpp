#include "ui/MainWindow.h"
#include "ui/dialog/Workspace.h"
#include "core/Constants.h"
#include "core/Settings.h"
#include <QApplication>
#include <QSettings>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    app.setOrganizationName(Const::App::Organization);
    app.setApplicationName(Const::App::Name);

#ifdef Q_OS_WIN
    QSettings::setDefaultFormat(QSettings::IniFormat);
#endif

    MainWindow mainWindow;
    mainWindow.show();

    if (!Settings::Project::isWorkspaceExists()) {
        Workspace workspace;
        workspace.exec();
    }

    return app.exec();
}
