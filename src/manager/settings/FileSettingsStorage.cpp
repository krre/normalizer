#include "FileSettingsStorage.h"
#include <QSettings>

FileSettingsStorage::FileSettingsStorage() {
}

void FileSettingsStorage::setMainWindow(const MainWindow& mainWindow) {
    QSettings settings;
    settings.beginGroup("MainWindow");

    settings.setValue("geometry", mainWindow.geometry);
    settings.setValue("state", mainWindow.state);

    settings.endGroup();
}

SettingsStorage::MainWindow FileSettingsStorage::mainWindow() const {
    MainWindow result;

    QSettings settings;
    settings.beginGroup("MainWindow");

    result.geometry = settings.value("geometry").toByteArray();
    result.state = settings.value("state").toByteArray();

    settings.endGroup();

    return result;
}

bool FileSettingsStorage::containsGeometry() const {
    QSettings settings;
    return settings.contains("MainWindow/geometry");
}

void FileSettingsStorage::setServerAddress(const ServerAddress& serverAddress) {
    QSettings settings;
    settings.beginGroup("Server");

    settings.setValue("host", serverAddress.host);
    settings.setValue("port", serverAddress.port);

    settings.endGroup();
}

SettingsStorage::ServerAddress FileSettingsStorage::serverAddress() const {
    ServerAddress result;

    QSettings settings;
    settings.beginGroup("Server");

    result.host = settings.value("host", "api.norm.dev").toByteArray();
    result.port = settings.value("port", 80).toInt();

    settings.endGroup();

    return result;
}

void FileSettingsStorage::setAccount(const Account& account) {
    QSettings settings;
    settings.setValue("Account/token", account.token);
}

SettingsStorage::Account FileSettingsStorage::account() const {
    QSettings settings;

    Account result;
    result.token = settings.value("Account/token").toString();

    return result;
}
