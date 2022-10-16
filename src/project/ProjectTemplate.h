#pragma once

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
    Norm::Expression* createExpression();

    ProjectManager* projectManager = nullptr;
};
