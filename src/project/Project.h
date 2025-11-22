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

    void create(const QString& name, const QString& directory, Target target);

private:
    QProcess* m_normProcess = nullptr;
};
