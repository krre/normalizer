#pragma once
#include <QString>

class ProjectSettings;

namespace Global {
    void init();
    ProjectSettings* projectSettings();
}
