#include "Project.h"
#include <QtCore>

Project::Project() {

}

void Project::create(const QString& path, NormCore::Project::Template projectTemplate) {
    QDir dir;
    dir.mkpath(path);

    qInfo().noquote() << "Project created:" << path ;
}
