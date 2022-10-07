#pragma once
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

    QString outputPath() const;

private:
    QString dirPath() const;
    QString filePath() const;

    QString m_projectPath;
    QJsonObject settings;
};
