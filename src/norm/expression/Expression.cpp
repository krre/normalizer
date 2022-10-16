#include "Expression.h"
#include <QDataStream>

namespace Norm {

Expression::Expression() {

}

void Expression::serialize(QDataStream& stream) const {
    Token::serialize(stream);
    FunctionId::serialize(stream);
    ExpressionId::serialize(stream);
    stream << m_index;
}

void Expression::deserialize(QDataStream& stream) {
    Token::deserialize(stream);
    FunctionId::deserialize(stream);
    ExpressionId::deserialize(stream);
    stream >> m_index;
}

void Expression::setIndex(quint16 index) {
    m_index = index;
}

quint16 Expression::index() const {
    return m_index;
}

}
