#include "FileSettings.h"
#include <QSettings>
#include <QDir>

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

void FileSettings::setDevelopmentServer(const DevelopmentServer& developmentServer) {
    QSettings settings;
    settings.beginGroup("DevelopmentServer");
    settings.setValue("url", developmentServer.url);
    settings.endGroup();
}

Settings::DevelopmentServer FileSettings::developmentServer() const {
    QSettings settings;
    settings.beginGroup("DevelopmentServer");

    DevelopmentServer result;
    result.url = settings.value("url", "https://api.norm.dev").toString();

    settings.endGroup();

    return result;
}

void FileSettings::setProjectTable(const ProjectTable& projectTable) {
    QSettings settings;
    settings.beginGroup("ProjectTable");

    settings.setValue("geometry", projectTable.geometry);
    settings.setValue("header", projectTable.header);

    settings.endGroup();
}

Settings::ProjectTable FileSettings::projectTable() const {
    QSettings settings;
    settings.beginGroup("ProjectTable");

    ProjectTable result;
    result.geometry = settings.value("geometry").toByteArray();
    result.header = settings.value("header").toByteArray();

    settings.endGroup();

    return result;
}

void FileSettings::setEditor(const Editor& editor) {
    QSettings settings;
    settings.beginGroup("Editor");
    settings.setValue("projectId", editor.projectId);
    settings.setValue("projectName", editor.projectName);
    settings.endGroup();
}

Settings::Editor FileSettings::editor() const {
    QSettings settings;
    settings.beginGroup("Editor");

    Editor result;
    result.projectId = settings.value("projectId").toInt();
    result.projectName = settings.value("projectName").toString();

    settings.endGroup();

    return result;
}

void FileSettings::setGraphics(const Graphics& graphics) {
    QSettings settings;
    settings.beginGroup("Graphics");
    settings.setValue("adapter", graphics.adapter);
    settings.endGroup();
}

Settings::Graphics FileSettings::graphics() const {
    QSettings settings;
    settings.beginGroup("Graphics");

    Graphics result;
    result.adapter = settings.value("adapter").toInt();

    settings.endGroup();

    return result;
}
