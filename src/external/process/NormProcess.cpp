#include "NormProcess.h"
#include "external/settings/Settings.h"
#include "core/Utils.h"
#include <QProcess>
#include <QDebug>

NormProcess::NormProcess(Settings* settings) {
    m_normPath = (settings->normLocation().type == Settings::NormLocation::Type::Home ? Utils::normHome() : settings->normLocation().directory) + "/bin/norm";
}

void NormProcess::createProject(const QString& name, const QString& directory, Project::Target target) {
    QProcess process;
    process.setWorkingDirectory(directory);
    QString targetArg = target == Project::Target::Application ? "--bin" : "--lib";
    process.start(m_normPath, { "create", name, targetArg });
    process.waitForStarted();
    process.waitForFinished();
}
