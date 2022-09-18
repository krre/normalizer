#pragma once
#include <NormCommon/Project.h>
#include <QJsonObject>

class ProjectSettings {
public:
    ProjectSettings();

    void create();
    void load();
    void save();
    void clear();

    bool isValid() const;

    QString projectPath() const;
    void setProjectPath(const QString& path);

    NormCommon::Project::Format format() const;
    void setFormat(NormCommon::Project::Format format);

private:
    QString dirPath() const;
    QString filePath() const;

    QString m_projectPath;
    QJsonObject settings;
};
