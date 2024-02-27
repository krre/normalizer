#pragma once
#include "Process.h"

class Settings;

class NormProcess : public Process {
public:
    NormProcess(Settings* settings);

    void createProject(const QString& name, const QString& directory, Project::Target target) override;

private:
    QString m_normPath;
};
