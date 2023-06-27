#include "MainWindow.h"
#include "core/Constants.h"
#include <QApplication>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    app.setOrganizationName(Const::App::Organization);
    app.setApplicationName(Const::App::Name);

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
