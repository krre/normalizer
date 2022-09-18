#pragma once
#include <NormCommon/Project.h>
#include <QJsonObject>

class ProjectSettings {
public:
    ProjectSettings(const QString& projectPath);

    void create();
    void load();
    void save();

    NormCommon::Project::Format format() const;
    void setFormat(NormCommon::Project::Format format);

private:
    QString dirPath() const;
    QString filePath() const;

    QString projectPath;
    QJsonObject settings;
};
