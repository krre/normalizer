#include "MainWindow.h"
#include "core/Application.h"

MainWindow::MainWindow() {
    setWindowTitle(Application::Name);
    resize(800, 600);
}
