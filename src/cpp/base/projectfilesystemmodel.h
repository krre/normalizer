#pragma once
#include <QFileSystemModel>
#include <QtCore>

class ProjectFileSystemModel : public QFileSystemModel
{
public:
    explicit ProjectFileSystemModel(QObject *parent = Q_NULLPTR);
};
