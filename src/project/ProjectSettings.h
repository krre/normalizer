#pragma once
#include <QJsonObject>

class ProjectSettings {
public:
    enum class Format {
        Binary,
        BinaryAndJson
    };

    ProjectSettings();

    void create();
    void load();
    void save();
    void clear();

    bool isValid() const;

    QString projectPath() const;
    void setProjectPath(const QString& path);

    Format format() const;
    void setFormat(Format format);

private:
    QString dirPath() const;
    QString filePath() const;

    QString m_projectPath;
    QJsonObject settings;
};
