#pragma once
#include <QObject>
#include <QUrl>
#include <QStandardPaths>

class Core : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString buildDate READ buildDate CONSTANT)
    Q_PROPERTY(QString qtVersion READ qtVersion CONSTANT)
    Q_PROPERTY(QString homePath READ homePath CONSTANT)

public:
    QString buildDate() { return QString(__DATE__); }
    QString qtVersion() { return QT_VERSION_STR; }
    Q_INVOKABLE QString urlToPath(const QUrl& url) { return url.toLocalFile(); }
    Q_INVOKABLE QString urlToFileName(const QUrl& url) { return url.fileName(); }
    Q_INVOKABLE QUrl pathToUrl(const QString& filePath) { return QUrl::fromLocalFile(filePath); }
    Q_INVOKABLE QString pathToBaseName(const QString& filePath);
    Q_INVOKABLE QString pathToFileName(const QString& path);
    Q_INVOKABLE static QString pathToDir(const QString& filePath);
    Q_INVOKABLE QString pathToExt(const QString& filePath);
    static QString homePath() { return QStandardPaths::writableLocation(QStandardPaths::HomeLocation); }
    Q_INVOKABLE bool isFileExists(const QString& filePath);
    Q_INVOKABLE bool isDirectoryExists(const QString& dirPath);
    Q_INVOKABLE bool removeFile(const QString& filePath);
    Q_INVOKABLE bool copyFile(const QString& fileName, const QString& newName);
    Q_INVOKABLE void saveFile(const QString& filePath, const QString& data);
    Q_INVOKABLE void renameFile(const QString& oldName, const QString& newName);
    Q_INVOKABLE QByteArray loadFile(const QString& filePath);
    Q_INVOKABLE void mkpath(const QString& dirPath);

};
