#pragma once
#include <QtCore>

class Utils : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString buildDate READ getBuildDate CONSTANT)

public:
    explicit Utils(QObject* parent = 0) { Q_UNUSED(parent) }
    QString getBuildDate() { return QString(__DATE__); }
    Q_INVOKABLE QString urlToPath(QUrl url);
    Q_INVOKABLE QString urlToFileName(QUrl url);
    Q_INVOKABLE QString homePath() { return QStandardPaths::writableLocation(QStandardPaths::HomeLocation); }
    Q_INVOKABLE static bool isFileExists(const QString& filePath);
    Q_INVOKABLE static void removeFile(const QString& path);
};
