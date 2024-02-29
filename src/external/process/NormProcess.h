#pragma once
#include "Process.h"

class NormProcess : public Process {
public:
    NormProcess(const QString& normDirectory);

    void createProject(const QString& name, const QString& directory, Project::Target target) override;

private:
    QString m_normPath;
};
