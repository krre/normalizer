#include "NormProcess.h"
#include <QProcess>
#include <QDebug>

NormProcess::NormProcess(const QString& normDirectory) {
    m_normPath = normDirectory + "/bin/norm";
}

void NormProcess::createProject(const QString& name, const QString& directory, Project::Target target) {
    QProcess process;
    process.setWorkingDirectory(directory);
    QString targetArg = target == Project::Target::Application ? "--bin" : "--lib";
    process.start(m_normPath, { "create", name, targetArg });
    process.waitForStarted();
    process.waitForFinished();
}
