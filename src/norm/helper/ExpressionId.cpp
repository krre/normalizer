#include "ExpressionId.h"
#include <QDataStream>

namespace Norm::Helper {

ExpressionId::ExpressionId() {

}

void ExpressionId::serialize(QDataStream& stream) const {
    stream << m_expressionId;
}

void ExpressionId::deserialize(QDataStream& stream) {
    stream >> m_expressionId;
}

void ExpressionId::setExpressionId(Id expressionId) {
    m_expressionId = expressionId;
}

Id ExpressionId::expressionId() const {
    return m_expressionId;
}

}
