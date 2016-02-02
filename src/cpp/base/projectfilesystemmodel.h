#pragma once
#include <QtCore>
#include <QFileSystemModel>

class ProjectFileSystemModel : public QFileSystemModel
{
    Q_OBJECT
    Q_PROPERTY(QString rootDir READ rootDir WRITE setRootDir NOTIFY rootDirChanged)
    Q_PROPERTY(QModelIndex rootIndex READ rootIndex NOTIFY rootIndexChanged)
public:
    explicit ProjectFileSystemModel(QObject *parent = Q_NULLPTR);
    QString rootDir() const { return rootPath(); }

    void setRootDir(const QString& rootDir)
    {
        if (rootPath() == rootDir) return;
        setRootPath(rootDir);
        emit rootDirChanged(rootDir);
        emit rootIndexChanged(rootIndex());
    }
    QModelIndex rootIndex() const
    {
        return index(rootPath());
    }

signals:
    void rootDirChanged(const QString& rootDir);
    void rootIndexChanged(const QModelIndex& rootIndex);
};
