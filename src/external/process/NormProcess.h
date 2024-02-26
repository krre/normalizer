#pragma once
#include "Process.h"

class NormProcess : public Process {
public:
    NormProcess();

    void createProject(const QString& name, const QString& directory, Project::Target target) override;
};
