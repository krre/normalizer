#pragma once
#include <QtCore>

class Settings : public QObject
{
    Q_OBJECT
public:
    explicit Settings(QObject* parent = 0);
    void setGeometry(const QMap<QString, int>& geometry);
    Q_INVOKABLE void setGeometryVar(const QVariantMap& geometry);
    QMap<QString, int> geometry();
    Q_INVOKABLE QVariantMap geometryVar();
    Q_INVOKABLE void setLang(const QString& lang);
    Q_INVOKABLE QString lang();
    Q_INVOKABLE void setRecentFiles(const QStringList& fileList);
    Q_INVOKABLE QStringList recentFiles();
    Q_INVOKABLE void setSession(const QStringList& fileList);
    Q_INVOKABLE QStringList session();
    Q_INVOKABLE void setSproutPath(const QString& path);
    Q_INVOKABLE QString sproutPath();
    Q_INVOKABLE void setRecentDirectory(const QString& path);
    Q_INVOKABLE QString recentDirectory();
    Q_INVOKABLE void setAutoLoadSession(bool value);
    Q_INVOKABLE bool autoLoadSession();

private:
    QSettings* settings;

};
