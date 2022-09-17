#include "Settings.h"
#include "core/Constants.h"
#include <QtCore>

namespace Settings {

constexpr auto Workspace = "Project/workspace";
constexpr auto RestoreSession = "Project/restoreSession";
constexpr auto OpenLastProject = "Project/openLast";
constexpr auto LastProject = "Project/last";
constexpr auto RecentProjects = "Project/recent";
constexpr auto RecentProjectPath = "path";

constexpr auto Geometry = "MainWindow/geometry";

void setValue(const QString& key, const QVariant& value) {
    QSettings settings;
    settings.setValue(key, value);
}

QVariant value(const QString& key, const QVariant& defaultValue) {
    QSettings settings;
    return settings.value(key, defaultValue);
}


bool contains(const QString& key) {
    QSettings settings;
    return settings.contains(key);
}

void remove(const QString& key) {
    QSettings settings;
    settings.remove(key);
}

namespace Project {

QString workspace() {
    return value(Workspace, QDir::homePath() + "/" + Const::Project::WorkspaceDir).toString();
}

void setWorkspace(const QString& workspace) {
    setValue(Workspace, workspace);
}

bool isWorkspaceExists() {
    if (!contains(Workspace)) {
        return false;
    }

    QDir dir(value(Workspace).toString());
    return dir.exists();
}

bool restoreSession() {
    return value(RestoreSession, true).toBool();
}

void setRestoreSession(bool restoreSession) {
    setValue(RestoreSession, restoreSession);
}

bool openLastProject() {
    return value(OpenLastProject, true).toBool();
}

void setOpenLastProject(bool openLastProject) {
    setValue(OpenLastProject, openLastProject);
}

QString lastProject() {
    return value(LastProject).toString();
}

void setLastProject(const QString& lastProject) {
    setValue(LastProject, lastProject);
}

QStringList recent() {
    QSettings settings;
    int size = settings.beginReadArray(RecentProjects);
    QStringList result;

    for (int i = 0; i < size; i++) {
        settings.setArrayIndex(i);
        result.append(settings.value(RecentProjectPath).toString());
    }

    return result;
}

void setRecent(const QStringList& recent) {
    if (recent.isEmpty()) {
        remove(RecentProjects);
        return;
    }

    QSettings settings;
    settings.beginWriteArray(RecentProjects);

    for (int i = 0; i < recent.count(); i++) {
        settings.setArrayIndex(i);
        settings.setValue(RecentProjectPath, recent.at(i));
    }

    settings.endArray();
}

}

namespace MainWindow {

QByteArray geometry() {
    return value(Geometry).toByteArray();
}

void setGeometry(const QByteArray& geometry) {
    setValue(Geometry, geometry);
}

}

}
