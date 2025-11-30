#include "Project.h"
#include <QProcess>
#include <QDir>

Project::Project(QObject* parent) : QObject(parent) {
    m_normProcess = new QProcess(this);
    m_normProcess->setProgram(CliTool);

    reset();
}

QString Project::name() const {
    return m_name;
}

QString Project::directory() const {
    return m_directory;
}

bool Project::isValid() const {
    return m_isValid;
}

Project::Target Project::target() const {
    return m_target;
}

void Project::create(const QString& name, const QString& directory, Target target) {
    QDir dir;
    dir.mkpath(directory);

    m_normProcess->setWorkingDirectory(directory);
    m_normProcess->setArguments({ "create", name, target == Target::Application ? "--app" : "--lib" });
    m_normProcess->start();
    m_normProcess->waitForFinished();

    m_name = name;
    m_directory = directory;
    m_target = target;

    m_isValid = true;
}

void Project::reset() {
    m_name = QString();
    m_directory = QString();
    m_isValid = false;
}
