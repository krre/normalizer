#pragma once
#include <QObject>
#include <QUrl>

class Core : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString buildDate READ buildDate CONSTANT)
    Q_PROPERTY(QString qtVersion READ qtVersion CONSTANT)

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
};
