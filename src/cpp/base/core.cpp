#include "core.h"

QString Core::pathToBaseName(const QString& path)
{
    QFileInfo fileInfo(path);
    return fileInfo.baseName();
}

QString Core::pathToDir(const QString &path)
{
    QFileInfo fileInfo(path);
    return fileInfo.dir().absolutePath();
}

bool Core::isFileExists(const QString& filePath)
{
    QFileInfo checkFile(filePath);
    return checkFile.exists() && checkFile.isFile();
}

bool Core::isDirectoryExists(const QString &dirPath)
{
    QDir dir(dirPath);
    return dir.exists();
}

bool Core::removeFile(const QString& filePath)
{
    return QFile::remove(filePath);
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

void Core::mkpath(const QString &dirPath) {
    QDir dir;
    dir.mkpath(dirPath);
}
