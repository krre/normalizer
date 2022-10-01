#include "Literal.h"

namespace Expression {

Literal::Literal(bool literal) : m_literal(literal), m_kind(Kind::Boolean) {

}

Literal::Literal(const QString& literal) : m_literal(literal), m_kind(Kind::String) {

}

Literal::Literal(double literal) : m_literal(literal), m_kind(Kind::Number) {

}

QVariant Literal::literal() const {
    return m_literal;
}

Literal::Kind Literal::kind() const {
    return m_kind;
}

}
