#include "NodeModel.h"

NodeModel::NodeModel() {}

QModelIndex NodeModel::index(int row, int column, const QModelIndex& parent) const {
    return QModelIndex();
}

QModelIndex NodeModel::parent(const QModelIndex& child) const {
    return QModelIndex();
}

int NodeModel::rowCount(const QModelIndex& parent) const {
    return 0;
}

int NodeModel::columnCount(const QModelIndex& parent) const {
    return 0;
}

QVariant NodeModel::data(const QModelIndex& index, int role) const {
    return QVariant();
}
