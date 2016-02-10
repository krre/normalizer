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
    Q_INVOKABLE QString path(const QModelIndex &index) { return filePath(index); }
    Q_INVOKABLE QModelIndex pathIndex(const QString& path) { return index(path); }
    Q_INVOKABLE bool removeFile(const QModelIndex &index) { return remove(index); }

    QString rootDir() const { return rootPath(); }
    void setRootDir(const QString& rootDir);

    QModelIndex rootIndex() const { return index(rootPath()); }

signals:
    void rootDirChanged(const QString& rootDir);
    void rootIndexChanged(const QModelIndex& rootIndex);
};
