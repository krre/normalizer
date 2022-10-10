#include "Global.h"
#include "core/Version.h"
#include "project/ProjectSettings.h"
#include "project/ProjectManager.h"
#include <QtCore>

namespace Global {

QScopedPointer<ProjectSettings> g_projectSettings;
QScopedPointer<ProjectManager> g_project;

void init() {
    g_projectSettings.reset(new ProjectSettings);
    g_project.reset(new ProjectManager);
}

ProjectSettings* projectSettings() {
    return g_projectSettings.data();
}

ProjectManager* project() {
    return g_project.data();
}

QVersionNumber Version::application() {
    return QVersionNumber(APP_MAJOR, APP_MINOR, APP_MICRO);
}

QVersionNumber Version::language() {
    return QVersionNumber(LANG_MAJOR, LANG_MINOR, LANG_MICRO);
}

}
