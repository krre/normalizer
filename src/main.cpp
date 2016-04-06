#include <QtWidgets>
#include "gui/MainWindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    app.setOrganizationName("Sprout Group");
    app.setApplicationName("Greenery");
    app.setApplicationVersion("0.1.0");

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
