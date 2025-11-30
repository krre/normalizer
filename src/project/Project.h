#pragma once
#include <QObject>

class QProcess;

class Project : QObject {
public:
    static constexpr auto CliTool = "norm";

    enum class Target {
        Application,
        Library
    };

    Project(QObject* parent);

    QString name() const;
    QString directory() const;
    Target target() const;

    void create(const QString& name, const QString& directory, Target target);

private:
    QString m_name;
    QString m_directory;
    Target m_target;

    QProcess* m_normProcess = nullptr;
};
