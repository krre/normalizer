#pragma once
#include <QString>

namespace Norm {
    class Project;
}

class ProjectWriter {
public:
    ProjectWriter();
    void write(Norm::Project* project, const QString& filePath);
};
