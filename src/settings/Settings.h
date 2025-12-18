#pragma once
#include <QVariant>

class Settings {
public:
    void setMainWindowGeometry(const  QByteArray& geometry);
    QByteArray mainWindowGeometry() const;

    void setMainWindowState(const  QByteArray& state);
    QByteArray mainWindowState() const;

    void setUiLoadLastProject(bool load);
    bool uiLoadLastProject() const;

    void setUiLastProjectPath(const QString& path);
    QString uiLastLoadPath() const;

    void setServerHost(const QString& host);
    QString serverHost() const;

    void setServerPort(int port);
    int serverPort() const;

    void setPathWorkspace(const QString& workspace);
    QString pathWorkspace() const;

    void setLoggingVulkan(bool enable);
    bool loggingVulkan() const;

protected:
    virtual void setValue(const QString& key, const QVariant& value) = 0;
    virtual QVariant value(const QString& key, const QVariant& defaultValue = QVariant()) const = 0;
};
