#pragma once
#include <QtCore>

class Settings : public QObject
{
    Q_OBJECT
public:
    explicit Settings(QObject *parent = 0);
    ~Settings() {}
    Q_INVOKABLE void setGeometry(const QVariantMap& geometry);
    Q_INVOKABLE QVariantMap getGeometry();
    Q_INVOKABLE void setLang(const QString& lang);
    Q_INVOKABLE QString getLang();
    Q_INVOKABLE void setRecentFiles(const QStringList& fileList);
    Q_INVOKABLE QStringList getRecentFiles();
    Q_INVOKABLE void setSession(const QStringList& fileList);
    Q_INVOKABLE QStringList getSession();
    Q_INVOKABLE void setSproutPath(const QString& path);
    Q_INVOKABLE QString getSproutPath();
    Q_INVOKABLE void setRecentDirectory(const QString& path);
    Q_INVOKABLE QString getRecentDirectory();

private:
    QSettings *settings;

};
