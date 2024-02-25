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

void FileSettings::setProjectLocation(const ProjectLocation& projectLocation) {
    QSettings settings;
    settings.beginGroup("ProjectLocation");
    settings.setValue("workspace", projectLocation.workspace);
    settings.setValue("host", projectLocation.host);
    settings.endGroup();
}

Settings::ProjectLocation FileSettings::projectLocation() const {
    QSettings settings;
    settings.beginGroup("ProjectLocation");

    ProjectLocation result;
    result.workspace = settings.value("workspace", QDir::homePath() + "/" + "NormProjects").toString();
    result.host = settings.value("host", "https://api.norm.dev").toString();

    settings.endGroup();

    return result;
}

void FileSettings::setNormLocation(const NormLocation& normLocation) {
    QSettings settings;
    settings.beginGroup("NormLocation");
    settings.setValue("type", int(normLocation.type));
    settings.setValue("directory", normLocation.directory);
    settings.endGroup();
}

Settings::NormLocation FileSettings::normLocation() const {
    QSettings settings;
    settings.beginGroup("NormLocation");

    NormLocation result;
    result.type = static_cast<NormLocation::Type>(settings.value("type").toInt());
    result.directory = settings.value("directory").toString();

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
    settings.setValue("selected", editor.selected);
    settings.endGroup();
}

Settings::Editor FileSettings::editor() const {
    QSettings settings;
    settings.beginGroup("Editor");

    Editor result;
    result.selected = settings.value("selected").toInt();

    settings.endGroup();

    return result;
}
