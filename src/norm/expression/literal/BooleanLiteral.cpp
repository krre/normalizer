#include "BooleanLiteral.h"
#include <QJsonValue>

namespace Expression {

BooleanLiteral::BooleanLiteral(bool literal, Node* parent) : Expression(parent), m_literal(literal) {

}

QJsonValue BooleanLiteral::serializeToJson() const {
    return m_literal;
}

}
