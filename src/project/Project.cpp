#include "Project.h"
#include "Session.h"
#include "core/Constants.h"
#include <QDir>

Project::Project(QObject* parent) : QObject(parent) {
    m_session = new Session(this);
}

void Project::create(const QString& name, const QString& directory, Template projectTemplate) {
    m_path = directory + "/" + name;

    QDir dir;
    dir.mkpath(m_path);

    m_session->create(m_path);

    QFile file(m_path + "/" + name + Const::Project::Extension);
    file.open(QIODeviceBase::WriteOnly);
    file.write(0);
}
