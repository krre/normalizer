#include "core.h"

QString Core::urlToPath(QUrl url)
{
    return url.toLocalFile();
}

QString Core::urlToFileName(QUrl url)
{
    return url.fileName().replace(".sprout", "");
}

bool Core::isFileExists(const QString& filePath)
{
    QFileInfo checkFile(filePath);
    // check if file exists and if yes: Is it really a file and no directory?
    return checkFile.exists() && checkFile.isFile();
}

void Core::removeFile(const QString& path)
{
    QDir dir;
    dir.remove(path);
}

PositionAttitudeTransform* Core::findUnit(const PositionAttitudeTransform* parentUnit, const QString& nameUnit) const
{
    return parentUnit->findChild<PositionAttitudeTransform*>(nameUnit);
}

void Core::saveFile(const QString& filePath, const QString& data)
{
    QFile file(filePath);
    if (file.open(QFile::WriteOnly | QFile::Text)) {
        QTextStream stream(&file);
        stream << data;
    } else {
        qDebug() << "Error opening file";
    }
    file.close();
}

QString Core::loadFile(const QString& filePath)
{
    QFile file(filePath);
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&file);
        QString data;
        while (!stream.atEnd()) {
            data.append(stream.readLine());
        }
        return data;
    } else {
        return QString();
    }
}
