#include "Project.h"
#include <QtCore>

Project::Project() {

}

void Project::create(const QString& path, NormCore::Project::Template projectTemplate) {
    qDebug() << path;
}
