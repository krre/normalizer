#pragma once
#include <QObject>

class QProcess;

class Project : QObject {
    Q_OBJECT
public:
    static constexpr auto CliTool = "norm";

    enum class State {
        Uninitialized,
        Ready
    };

    enum class Target {
        Application,
        Library
    };

    Project(QObject* parent);

    State state() const;

    QString name() const;
    QString directory() const;
    Target target() const;

    bool isValid() const;

    void create(const QString& name, const QString& directory, Target target);
    void reset();

signals:
    void stateChanged(Project::State state);

private:
    void setState(State state);

    State m_state = State::Uninitialized;

    QString m_name;
    QString m_directory;
    Target m_target = Target::Application;

    QProcess* m_normProcess = nullptr;
};
