#include "BooleanLiteral.h"

namespace Expression {

BooleanLiteral::BooleanLiteral(bool literal, Node* parent) : Expression(parent), m_literal(literal) {

}

}
