#include "Project.h"
#include <QDebug>

Project::Project(QObject* parent) : QObject(parent) {

}

void Project::create(const QString& name, const QString& directory, Target target) {
    qDebug() << name << directory;
}
