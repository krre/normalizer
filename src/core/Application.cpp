#include "Application.h"
#include "external/network/RestApi.h"
#include <QMainWindow>
#include <QMessageBox>
#include <QSettings>

Application::Application(int& argc, char* argv[]) : QApplication(argc, argv) {
    setOrganizationName(Organization);
    setApplicationName(Name);

#ifdef Q_OS_WIN
    QSettings::setDefaultFormat(QSettings::IniFormat);
#endif
}

bool Application::notify(QObject* receiver, QEvent* event) {
    try {
        return QApplication::notify(receiver, event);
    } catch (RestException& e) {
        showErrorMessage(e.message());
    } catch (const std::exception& e) {
        showErrorMessage(e.what());
    }

    return false;
}

void Application::showErrorMessage(const QString& message) const {
    for (QWidget* widget : QApplication::topLevelWidgets()) {
        if (dynamic_cast<QMainWindow*>(widget)) {
            QMessageBox::critical(widget, Name, message);
            return;
        }
    }

    qCritical().noquote() << "Exception:" << message;
}
