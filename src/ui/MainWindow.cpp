#include "MainWindow.h"
#include "core/Application.h"

MainWindow::MainWindow() {
    setWindowTitle(Application::applicationName());
    resize(800, 600);
}
