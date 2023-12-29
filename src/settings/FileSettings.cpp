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
    settings.beginGroup("Server");

    settings.setValue("api", server.api.toString());
    settings.setValue("editor", server.editor.toString());

    settings.endGroup();
}

Settings::Server FileSettings::server() const {\
    QSettings settings;
    settings.beginGroup("Server");

    Server result;
    result.api = settings.value("api", "https://api.norm.dev").toString();
    result.editor = settings.value("editor", "http://localhost:5173/editor").toString();

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

void FileSettings::setProject(const Project& project) {
    QSettings settings;
    settings.beginGroup("Project");

    settings.setValue("id", project.id);
    settings.setValue("name", project.name);

    settings.endGroup();
}

Settings::Project FileSettings::project() const {
    QSettings settings;
    settings.beginGroup("Project");

    Project result;
    result.id = settings.value("id", 0).toLongLong();
    result.name = settings.value("name").toString();

    settings.endGroup();

    return result;
}
