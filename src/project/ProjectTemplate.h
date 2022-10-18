#pragma once
#include "norm/project/Project.h"

namespace Norm {
    class Expression;
}

class ProjectManager;

class ProjectTemplate {
public:
    ProjectTemplate(ProjectManager* projectManager);

    void createApp();
    void createLib();

private:
    void createProject(Norm::Project::Target target);
    Norm::Expression* createExpression();

    ProjectManager* projectManager = nullptr;
};
