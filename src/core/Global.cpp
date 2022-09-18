#include "Global.h"
#include "project/ProjectSettings.h"
#include <QtCore>

namespace Global {

QScopedPointer<ProjectSettings> g_projectSettings;

void init() {
    g_projectSettings.reset(new ProjectSettings);
}

ProjectSettings* projectSettings() {
    return g_projectSettings.data();
}

}
