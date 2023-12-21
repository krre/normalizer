#include "Application.h"
#include "core/Constants.h"
#include "network/http/HttpNetwork.h"
#include <QMainWindow>
#include <QMessageBox>

Application::Application(int& argc, char* argv[]) : QApplication(argc, argv) {
    setOrganizationName(Const::App::Organization);
    setApplicationName(Const::App::Name);
}

bool Application::notify(QObject* receiver, QEvent* event) {
    try {
        return QApplication::notify(receiver, event);
    } catch (HttpException& e) {
        showErrorMessage(e.message());
    } catch (const std::exception& e) {
        showErrorMessage(e.what());
    }

    return false;
}

void Application::showErrorMessage(const QString& message) const {
    for (QWidget* widget : QApplication::topLevelWidgets()) {
        if (dynamic_cast<QMainWindow*>(widget)) {
            QMessageBox::critical(widget, widget->windowTitle(), message);
            return;
        }
    }

    qCritical().noquote() << "Exception:" << message;
}
