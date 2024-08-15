#include "Core.h"
#include <QtCore>

QString Core::pathToBaseName(const QString& filePath) {
    QFileInfo fileInfo(filePath);
    return fileInfo.baseName();
}

QString Core::pathToFileName(const QString& path) {
    QFileInfo fileInfo(path);
    return fileInfo.fileName();
}

QString Core::pathToDir(const QString& filePath) {
    QFileInfo fileInfo(filePath);
    return fileInfo.dir().absolutePath();
}

QString Core::pathToExt(const QString& filePath) {
    QFileInfo fileInfo(filePath);
    return fileInfo.suffix();
}

bool Core::isFileExists(const QString& filePath) {
    QFileInfo fileInfo(filePath);
    return fileInfo.exists() && fileInfo.isFile();
}

bool Core::isDirectoryExists(const QString& dirPath) {
    QDir dir(dirPath);
    return dir.exists();
}

bool Core::removeFile(const QString& filePath) {
    return QFile::remove(filePath);
}

bool Core::copyFile(const QString& fileName, const QString& newName) {
    return QFile::copy(fileName, newName);
}

void Core::saveFile(const QString& filePath, const QString& data) {
    QFile file(filePath);
    if (file.open(QFile::WriteOnly | QFile::Text)) {
        QTextStream stream(&file);
        stream << data;
    } else {
        qDebug() << "Error opening file";
    }
    file.close();
}

void Core::renameFile(const QString& oldName, const QString& newName) {
    QFile::rename(oldName, newName);
}

QByteArray Core::loadFile(const QString& filePath) {
    QFile file(filePath);
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&file);
        QByteArray data;
        data.append(stream.readAll());
        return data;
    } else {
        return QByteArray();
    }
}

void Core::mkpath(const QString& dirPath) {
    QDir dir;
    dir.mkpath(dirPath);
}
