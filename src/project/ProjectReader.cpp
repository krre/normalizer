#include "ProjectReader.h"
#include "norm/Project.h"
#include <QtCore>

ProjectReader::ProjectReader() {

}

std::unique_ptr<Norm::Project> ProjectReader::read(const QString& filePath) {
    QFile file(filePath);

    if (!file.open(QIODeviceBase::ReadOnly | QIODevice::Text)) {
        throw std::runtime_error(QString("Failed to read file %1").arg(filePath).toStdString().c_str());
    }

    QTextStream in(&file);
    QString line;

    while (in.readLineInto(&line)) {
        QStringList words = line.split(' ');
        QString tokenName = words.first();

        qDebug() << words;

        if (tokenName == "norm") {

        } else if (tokenName == "project") {

        }
    }

    auto result = std::make_unique<Norm::Project>();
    return result;
}
