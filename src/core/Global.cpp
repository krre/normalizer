#include "Global.h"
#include "project/ProjectSettings.h"
#include "project/Project.h"
#include <QtCore>

namespace Global {

QScopedPointer<ProjectSettings> g_projectSettings;
QScopedPointer<Project> g_project;

void init() {
    g_projectSettings.reset(new ProjectSettings);
    g_project.reset(new Project);
}

ProjectSettings* projectSettings() {
    return g_projectSettings.data();
}

Project* project() {
    return g_project.data();
}

}
