#pragma once
#include <QString>
#include <NormCore/Global.h>

class Project {
public:
    Project();
    void create(const QString& path, NormCore::Project::Template projectTemplate);
};
