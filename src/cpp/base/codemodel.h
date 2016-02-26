#pragma once

#include <QtCore>

class CodeModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit CodeModel(QObject *parent = 0);

private:
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
};