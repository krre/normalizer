#include "FileSettings.h"
#include <QSettings>

FileSettings::FileSettings() {
}

void FileSettings::setMainWindow(const MainWindow& mainWindow) {
    QSettings settings;
    settings.beginGroup("MainWindow");

    settings.setValue("geometry", mainWindow.geometry);
    settings.setValue("state", mainWindow.state);

    settings.endGroup();
}

Settings::MainWindow FileSettings::mainWindow() const {
    MainWindow result;

    QSettings settings;
    settings.beginGroup("MainWindow");

    result.geometry = settings.value("geometry").toByteArray();
    result.state = settings.value("state").toByteArray();

    settings.endGroup();

    return result;
}

bool FileSettings::containsGeometry() const {
    QSettings settings;
    return settings.contains("MainWindow/geometry");
}

void FileSettings::setServerAddress(const ServerAddress& serverAddress) {
    QSettings settings;
    settings.beginGroup("Server");

    settings.setValue("host", serverAddress.host);
    settings.setValue("port", serverAddress.port);

    settings.endGroup();
}

Settings::ServerAddress FileSettings::serverAddress() const {
    ServerAddress result;

    QSettings settings;
    settings.beginGroup("Server");

    result.host = settings.value("host", "api.norm.dev").toByteArray();
    result.port = settings.value("port", 80).toInt();

    settings.endGroup();

    return result;
}

void FileSettings::setAccount(const Account& account) {
    QSettings settings;
    settings.setValue("Account/token", account.token);
}

Settings::Account FileSettings::account() const {
    QSettings settings;

    Account result;
    result.token = settings.value("Account/token").toString();

    return result;
}
