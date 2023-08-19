#include "ui/MainWindow.h"
#include "core/Constants.h"
#include "core/Settings.h"
#include <QApplication>

int main(int argc, char* argv[]) {
    // Hack to fix styling with Qt 6.5 on GTK3
    qunsetenv("GNOME_DESKTOP_SESSION_ID");
    qunsetenv("XDG_CURRENT_DESKTOP");

    QApplication app(argc, argv);
    app.setOrganizationName(Const::App::Organization);
    app.setApplicationName(Const::App::Name);

    Settings::init();

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
