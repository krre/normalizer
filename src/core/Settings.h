#pragma once
#include <QVariant>

namespace Settings {
    void setValue(const QString& key, const QVariant& value);
    QVariant value(const QString& key, const QVariant& defaultValue = QVariant());
    bool contains(const QString& key);

namespace Project {
    QString workspace();
    void setWorkspace(const QString& workspace);
    bool isWorkspaceExists();

    bool restoreSession();
    void setRestoreSession(bool restoreSession);
}

namespace MainWindow {
    QByteArray geometry();
    void setGeometry(const QByteArray& geometry);
}

};
