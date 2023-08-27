#include "ProjectWriter.h"
#include "norm/Project.h"
#include "core/Constants.h"
#include <QtCore>

ProjectWriter::ProjectWriter() {

}

void ProjectWriter::write(Norm::Project* project, const QString& filePath) {
    QFile file(filePath);

    if (!file.open(QIODeviceBase::WriteOnly | QIODevice::Text)) {
        throw std::runtime_error(QString("Failed to write file %1").arg(filePath).toStdString().c_str());
    }

    QTextStream out(&file);
    out << "norm " << "version " << Const::Norm::Version << Qt::endl;
    out << "project " << "name " << project->name() << " template " << (project->projectTemplate() == Norm::Project::Template::Binary ? "bin" : "lib") << Qt::endl;
}
