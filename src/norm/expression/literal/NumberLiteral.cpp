#include "NumberLiteral.h"

namespace Expression {

NumberLiteral::NumberLiteral(double literal, Node* parent) : Expression(parent), m_literal(literal) {

}

}
