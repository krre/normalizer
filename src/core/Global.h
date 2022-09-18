#pragma once
#include <QString>

class ProjectSettings;

namespace NormCommon {
    class Project;
}

namespace Global {
    void init();

    ProjectSettings* projectSettings();
    NormCommon::Project* project();
}
