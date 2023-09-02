#include "ProjectWriter.h"
#include "core/Exception.h"
#include "norm/Project.h"
#include <QtCore>

ProjectWriter::ProjectWriter() {

}

void ProjectWriter::write(Norm::Project* project, const QString& filePath) {
    QFile file(filePath);

    if (!file.open(QIODeviceBase::WriteOnly | QIODevice::Text)) {
        throw Exception("Failed to write file '{}'", filePath);
    }

    QTextStream out(&file);
    out << project->serialize() << Qt::endl;
}
