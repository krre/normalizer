#include "Settings.h"
#include "core/Constants.h"
#include <QtCore>

namespace Settings {

constexpr auto Workspace = "Project/workspace";
constexpr auto RestoreSession = "Project/restoreSession";
constexpr auto OpenLastProject = "Project/openLast";
constexpr auto LastProject = "Project/last";

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
