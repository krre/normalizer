#include "ProjectReader.h"
#include "core/Exception.h"
#include "norm/Project.h"
#include "norm/Sign.h"
#include <QtCore>

ProjectReader::ProjectReader() {

}

std::unique_ptr<Norm::Project> ProjectReader::read(const QString& filePath) {
    QFile file(filePath);

    if (!file.open(QIODeviceBase::ReadOnly | QIODevice::Text)) {
        throw Exception("Failed to read file '{}'", filePath);
    }

    QTextStream in(&file);
    QString line;

    auto project = std::make_unique<Norm::Project>();

    while (in.readLineInto(&line)) {
        QString sign = line.first(4);
        using namespace Norm;

        if (sign == Sign::Norm) {

        } else if (sign == Sign::Project) {
            project->parse(line.mid(5));
        }
    }

    return project;
}
