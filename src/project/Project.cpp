#include "Project.h"
#include "core/Constants.h"
#include <QDir>

Project::Project(QObject* parent) : QObject(parent) {

}

void Project::create(const QString& name, const QString& directory, Template projectTemplate) {
    QString projectPath = directory + "/" + name;

    QDir dir;
    dir.mkpath(projectPath);

    QFile file(projectPath + "/" + name + Const::Project::Extension);
    file.open(QIODeviceBase::WriteOnly);
    file.write(0);
}
