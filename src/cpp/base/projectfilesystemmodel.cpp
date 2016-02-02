#include "projectfilesystemmodel.h"

ProjectFileSystemModel::ProjectFileSystemModel(QObject *parent)
    : QFileSystemModel(parent)
{
    setRootPath(QDir::homePath());
    setResolveSymlinks(true);
}

void ProjectFileSystemModel::setRootDir(const QString &rootDir)
{
    if (rootPath() == rootDir) return;
    setRootPath(rootDir);
    emit rootDirChanged(rootDir);
    emit rootIndexChanged(rootIndex());
}
