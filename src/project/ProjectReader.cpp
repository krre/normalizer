#include "ProjectReader.h"
#include "core/Exception.h"
#include "norm/Project.h"
#include <QtCore>

ProjectReader::ProjectReader() {

}

std::unique_ptr<Norm::Project> ProjectReader::read(const QString& filePath) {
    QFile file(filePath);

    if (!file.open(QFile::ReadOnly)) {
        throw Exception("Failed to read file '{}'", filePath);
    }

    QDataStream stream(&file);

    while (!stream.atEnd()) {
        Norm::TokenType type;
        stream >> type;

        qDebug() << "type" << int(type);
    }

    auto project = std::make_unique<Norm::Project>();


    return project;
}
