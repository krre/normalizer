#include "TestProcess.h"

TestProcess::TestProcess() {}

void TestProcess::createProject(const QString& name, const QString& directory, Project::Target target) {
    m_projectName = name;
    m_projectDirectory = directory;
    m_projectTarget = target;
}
