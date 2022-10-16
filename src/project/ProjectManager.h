#pragma once
#include "norm/project/Project.h"
#include <QString>
#include <QScopedPointer>

namespace Norm {
    class Project;
    class Flow;
}

class Database;
class TokenFactory;

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
    void read(const QString& filePath);

    Norm::Token* createToken(Norm::Code code) const;
    void removeToken(Norm::Token* token);

private:
    QString m_path;
    QScopedPointer<TokenFactory> tokenFactory;
    QScopedPointer<Database> database;
};
