#pragma once
#include <QtCore>

class Settings : public QObject
{
    Q_OBJECT
public:
    explicit Settings(QObject* parent = 0);
    void setGeometry(const QMap<QString, int>& geometry);
    QMap<QString, int> geometry();
    void setLang(const QString& lang);
    QString lang();
    void setRecentFiles(const QStringList& fileList);
    QStringList recentFiles();
    void setSession(const QStringList& fileList);
    QStringList session();
    void setSproutPath(const QString& path);
    QString sproutPath();
    void setRecentDirectory(const QString& path);
    QString recentDirectory();
    void setAutoLoadSession(bool value);
    bool autoLoadSession();

private:
    QSettings* settings;

};
