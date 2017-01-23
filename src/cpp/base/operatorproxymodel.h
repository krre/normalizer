#pragma once
#include <QSortFilterProxyModel>

class OperatorProxyModel : public QSortFilterProxyModel {
    Q_OBJECT
public:
    Q_INVOKABLE void setFilterPattern(const QString& pattern);
    Q_INVOKABLE int sourceIndex(int row);
};
