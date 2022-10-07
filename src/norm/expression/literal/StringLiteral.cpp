#include "StringLiteral.h"

namespace Expression {

StringLiteral::StringLiteral(const QString& literal, Node* parent) : Expression(parent), m_literal(literal) {

}

}
