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
