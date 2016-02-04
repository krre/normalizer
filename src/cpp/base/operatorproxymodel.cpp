#include "operatorproxymodel.h"

OperatorProxyModel::OperatorProxyModel()
{

}

void OperatorProxyModel::setFilterPattern(const QString& pattern)
{
    if (filterRegExp().pattern() == pattern) {
        return;
    }
    setFilterRegExp(QRegExp(pattern, Qt::CaseInsensitive, QRegExp::RegExp));
}

