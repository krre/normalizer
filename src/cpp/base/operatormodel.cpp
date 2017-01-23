#include "operatormodel.h"

OperatorModel::OperatorModel(QObject* parent) : QAbstractListModel(parent) {
    roles << "name" << "shortcut";
}

void OperatorModel::addOperator(const QVariantMap& operatorMap) {
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    operators << operatorMap;
    endInsertRows();
}

int OperatorModel::rowCount(const QModelIndex& parent) const {
    Q_UNUSED(parent);
    return operators.count();
}

QVariant OperatorModel::data(const QModelIndex& index, int role) const {
    if (index.row() < 0 || index.row() >= operators.count())
        return QVariant();

    int roleIndex = role - Qt::UserRole - 1;
    const QVariantMap& operatorMap = operators[index.row()].toMap();
    return operatorMap[roles.at(roleIndex)];
}

QHash<int, QByteArray> OperatorModel::roleNames() const {
    QHash<int, QByteArray> rolesHash;
    int role = Qt::UserRole + 1;
    for (int i = 0; i < roles.count(); i++) {
        rolesHash[role + i] = roles.at(i).toLatin1();
    }

    return rolesHash;
}
