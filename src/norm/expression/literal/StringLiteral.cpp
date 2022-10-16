#include "StringLiteral.h"
#include "core/Constants.h"

namespace Norm {

StringLiteral::StringLiteral() {

}

Code StringLiteral::code() const {
    return Const::Norm::Token::StringLiteral;
}

void StringLiteral::serialize(QDataStream& stream) const {
    stream << m_literal;
}

void StringLiteral::deserialize(QDataStream& stream) {
    stream >> m_literal;
}

void StringLiteral::setLiteral(const QString& literal) {
    m_literal = literal;
}

const QString& StringLiteral::literal() const {
    return m_literal;
}

}
