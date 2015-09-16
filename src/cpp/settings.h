#pragma once
#include <QtCore>

class Settings : public QObject
{
    Q_OBJECT
public:
    explicit Settings(QObject* parent = 0);
    void setGeometry(const QMap<QString, int>& geometry);
    QMap<QString, int> getGeometry();
    void setLang(const QString& lang);
    QString getLang();
    void setRecentFiles(const QStringList& fileList);
    QStringList getRecentFiles();
    void setSession(const QStringList& fileList);
    QStringList getSession();
    void setSproutPath(const QString& path);
    QString getSproutPath();
    void setRecentDirectory(const QString& path);
    QString getRecentDirectory();
    void setAutoLoadSession(bool value);
    bool getAutoLoadSession();

private:
    QSettings* settings;

};
