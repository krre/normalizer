#include "NormProcess.h"
#include "external/settings/Settings.h"
#include <QProcess>
#include <QDebug>

NormProcess::NormProcess(Settings* settings) {
    m_normPath = settings->normDirectory() + "/bin/norm";
}

void NormProcess::createProject(const QString& name, const QString& directory, Project::Target target) {
    QProcess process;
    process.setWorkingDirectory(directory);
    QString targetArg = target == Project::Target::Application ? "--bin" : "--lib";
    process.start(m_normPath, { "create", name, targetArg });
    process.waitForStarted();
    process.waitForFinished();
}
