#include "Project.h"
#include "Session.h"
#include "core/Constants.h"
#include "core/Settings.h"
#include <QDir>

Project::Project(QObject* parent) : QObject(parent) {
    m_session = new Session(this);
    m_opened.setBinding([&] { return !m_path.value().isEmpty(); });
}

void Project::create(const QString& name, const QString& directory, Template projectTemplate) {
    QString path = directory + "/" + name;

    QDir dir;
    dir.mkpath(path);

    m_session->create(path);

    QFile file(path + "/" + name + Const::Project::Extension);
    file.open(QIODeviceBase::WriteOnly);
    file.write(0);

    open(path);
}

void Project::open(const QString& path) {
    QDir dir(path);

    if (!dir.exists()) {
        return;
    }

    m_path = path;
    Settings::setValue<General::LastProject>(m_path);
}

void Project::save() {

}

void Project::close() {
    m_path = "";
}
