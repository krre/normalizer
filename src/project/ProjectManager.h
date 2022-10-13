#pragma once
#include "norm/project/Project.h"
#include <QString>
#include <QScopedPointer>

namespace Norm {
    class Project;
    class Flow;
}

class ProjectManager {
public:
    ProjectManager();
    ~ProjectManager();

    QString path() const;
    Norm::Project::Target target() const;

    void create(const QString& path, Norm::Project::Target target);
    void open(const QString& path);
    void close();

    void write(const QString& filePath);
    void read(const QString& path);

private:
    void createApp();
    void createLib();
    void createFlow(Norm::Flow* flow);

    QString m_path;
    QScopedPointer<Norm::Project> m_project;
};
