#include "operatorproxymodel.h"
#include <QtCore>

void OperatorProxyModel::setFilterPattern(const QString& pattern) {
    if (filterRegExp().pattern() == pattern) {
        return;
    }
    setFilterRegExp(QRegExp(pattern, Qt::CaseInsensitive, QRegExp::RegExp));
}

int OperatorProxyModel::sourceIndex(int row) {
    return mapToSource(index(row, 0)).row();
}
