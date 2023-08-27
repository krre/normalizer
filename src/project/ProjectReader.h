#pragma once
#include <QString>

namespace Norm {
    class Project;
}

class ProjectReader {
public:
    ProjectReader();
    std::unique_ptr<Norm::Project> read(const QString& filePath);

private:

};

