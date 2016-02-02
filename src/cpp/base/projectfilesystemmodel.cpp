#include "projectfilesystemmodel.h"

ProjectFileSystemModel::ProjectFileSystemModel(QObject *parent)
    : QFileSystemModel(parent)
{
    setRootPath(QDir::homePath());
    setResolveSymlinks(true);
}
