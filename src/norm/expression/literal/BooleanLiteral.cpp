#include "BooleanLiteral.h"
#include "core/Constants.h"

namespace Norm {

BooleanLiteral::BooleanLiteral() {

}

Code BooleanLiteral::code() const {
    return Const::Norm::Token::BooleanLiteral;
}

void BooleanLiteral::serialize(QDataStream& stream) const {
    stream << m_literal;
}

void BooleanLiteral::deserialize(QDataStream& stream) {
    stream >> m_literal;
}

void BooleanLiteral::setLiteral(bool literal) {
    m_literal = literal;
}

bool BooleanLiteral::literal() const {
    return m_literal;
}

}
