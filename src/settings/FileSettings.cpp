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

void FileSettings::setServer(const Server& server) {
    QSettings settings;
    settings.setValue("url", server.url.toString());
}

Settings::Server FileSettings::server() const {
    Server result;

    QSettings settings;
    result.url = settings.value("url", "https://api.norm.dev").toByteArray();

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

void FileSettings::setProject(const Project& project) {
    QSettings settings;
    settings.setValue("Project/id", project.id);
}

Settings::Project FileSettings::project() const {
    QSettings settings;

    Project result;
    result.id = settings.value("Project/id", 0).toLongLong();

    return result;
}
