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
