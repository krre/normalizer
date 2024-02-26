#pragma once
#include "program/Project.h"

class Process {
public:
    Process();

    virtual void createProject(const QString& name, const QString& directory, Project::Target target) = 0;
};
