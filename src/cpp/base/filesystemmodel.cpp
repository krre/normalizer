#include "filesystemmodel.h"

FileSystemModel::FileSystemModel(QObject* parent) : QFileSystemModel(parent) {
    setRootPath(QDir::homePath());
    setResolveSymlinks(true);
}

void FileSystemModel::setRootDir(const QString& rootDir) {
    if (rootPath() == rootDir) return;
    setRootPath(rootDir);
    emit rootDirChanged(rootDir);
    emit rootIndexChanged(rootIndex());
}
