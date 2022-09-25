#pragma once
#include <QJsonObject>


class GuiSession {
public:
    GuiSession();

    void read(const QString& projectPath);
    void write();

private:
    QString dirPath() const;
    QString filePath() const;

    QString m_projectPath;
    QJsonObject session;
};
