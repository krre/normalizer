#include "Application.h"
#include "core/Constants.h"
#include "network/http/HttpNetwork.h"
#include "ui/MainWindow.h"
#include <QMessageBox>

Application::Application(int& argc, char* argv[]) : QApplication(argc, argv) {
    setOrganizationName(Const::App::Organization);
    setApplicationName(Const::App::Name);
}

void Application::setMainWindow(MainWindow* mainWindow) {
    m_mainWindow = mainWindow;
}

bool Application::notify(QObject* receiver, QEvent* event) {
    try {
        return QApplication::notify(receiver, event);
    } catch (HttpException& e) {
        QMessageBox::critical(m_mainWindow, m_mainWindow->windowTitle(), e.message());
    } catch (const std::exception& e) {
        QMessageBox::critical(m_mainWindow, m_mainWindow->windowTitle(), e.what());
    }

    return false;
}
