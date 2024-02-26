#pragma once
#include "external/process/Process.h"

class TestProcess : public Process {
public:
    TestProcess();

    void createProject(const QString& name, const QString& directory, Project::Target target) override;

    QString m_projectName;
    QString m_projectDirectory;
    Project::Target m_projectTarget;
};
