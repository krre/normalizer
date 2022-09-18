#include "Global.h"
#include "project/ProjectSettings.h"
#include <QtCore>

namespace Global {

QScopedPointer<ProjectSettings> g_projectSettings;
QScopedPointer<NormCommon::Project> g_project;

void init() {
    g_projectSettings.reset(new ProjectSettings);
    g_project.reset(new NormCommon::Project);
}

ProjectSettings* projectSettings() {
    return g_projectSettings.data();
}

NormCommon::Project* project() {
    return g_project.data();
}

}
