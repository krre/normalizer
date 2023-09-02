#include "ProjectWriter.h"
#include "core/Exception.h"
#include "norm/Project.h"
#include <QtCore>

ProjectWriter::ProjectWriter() {

}

void ProjectWriter::write(Norm::Project* project, const QString& filePath) {
    QFile file(filePath);

    if (!file.open(QFile::WriteOnly)) {
        throw Exception("Failed to write file '{}'", filePath);
    }

    file.write(project->serialize());
}
