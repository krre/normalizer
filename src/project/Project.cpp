#include "Project.h"
#include <QProcess>
#include <QDir>

Project::Project(QObject* parent) : QObject(parent) {
    m_normProcess = new QProcess(this);
    m_normProcess->setProgram("norm");
}

void Project::create(const QString& name, const QString& directory, Target target) {
    QDir dir;
    dir.mkpath(directory);

    m_normProcess->setWorkingDirectory(directory);
    m_normProcess->setArguments({ "create", name, target == Target::Application ? "--app" : "--lib" });
    m_normProcess->start();
}
