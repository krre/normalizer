#pragma once
#include <QString>

class ProjectSettings;
class Project;

namespace Global {
    void init();

    ProjectSettings* projectSettings();
    Project* project();
}
