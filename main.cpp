#include <QApplication>
#include <QMainWindow>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QMainWindow mainWindow;
    mainWindow.resize(800, 600);
    mainWindow.setWindowTitle("Greenery");
    mainWindow.show();

    return app.exec();
}
