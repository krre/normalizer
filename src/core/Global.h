#pragma once
#include <QString>
#include <QVersionNumber>

class ProjectSettings;
class ProjectManager;

namespace Global {
    namespace Version {
        QVersionNumber application();
        QVersionNumber language();
    }

    void init();

    ProjectSettings* projectSettings();
    ProjectManager* project();


}
