#include "Application.h"
#include "external/network/RestApi.h"
#include <QSettings>

Application::Application(int& argc, char* argv[]) : QGuiApplication(argc, argv) {
    setOrganizationName(Organization);
    setApplicationName(Name);

#ifdef Q_OS_WIN
    QSettings::setDefaultFormat(QSettings::IniFormat);
#endif
}

bool Application::notify(QObject* receiver, QEvent* event) {
    try {
        return QGuiApplication::notify(receiver, event);
    } catch (RestException& e) {
        qCritical().noquote() << e.message();
    } catch (const std::exception& e) {
        qCritical().noquote() << e.what();
    }

    return false;
}
