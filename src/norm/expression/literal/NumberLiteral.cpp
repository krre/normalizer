#include "NumberLiteral.h"
#include "core/Constants.h"

namespace Norm {

NumberLiteral::NumberLiteral() {

}

Code NumberLiteral::code() const {
    return Const::Norm::Token::NumberLiteral;
}

void NumberLiteral::serialize(QDataStream& stream) const {
    stream << m_literal;
}

void NumberLiteral::deserialize(QDataStream& stream) {
    stream >> m_literal;
}

void NumberLiteral::setLiteral(double literal) {
    m_literal = literal;
}

double NumberLiteral::literal() const {
    return m_literal;
}

}
