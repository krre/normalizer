#pragma once
#include <QtCore>

class OperatorModel : public QAbstractListModel
{
    Q_OBJECT
public:
    OperatorModel(QObject* parent = 0);
    Q_INVOKABLE void addOperator(const QVariantMap& operatorMap);
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

protected:
    QHash<int, QByteArray> roleNames() const;
private:
    QStringList roles;
    QVariantList operators;
};
