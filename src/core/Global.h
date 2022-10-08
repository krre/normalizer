#pragma once
#include <QString>
#include <QVersionNumber>

class ProjectSettings;
class Project;

namespace Global {
    namespace Version {
        QVersionNumber application();
        QVersionNumber language();
    }

    void init();

    ProjectSettings* projectSettings();
    Project* project();


}
