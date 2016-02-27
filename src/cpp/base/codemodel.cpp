#include "codemodel.h"

CodeModel::CodeModel(QObject* parent) : QAbstractItemModel(parent)
{

}

CodeModel::addNode(Node* parent, Node* node)
{
    qDebug() << parent << node;
}

QModelIndex CodeModel::index(int row, int column, const QModelIndex& parent) const
{

}

QModelIndex CodeModel::parent(const QModelIndex& child) const
{

}

int CodeModel::rowCount(const QModelIndex& parent) const
{

}

int CodeModel::columnCount(const QModelIndex& parent) const
{

}

QVariant CodeModel::data(const QModelIndex& index, int role) const
{

}
