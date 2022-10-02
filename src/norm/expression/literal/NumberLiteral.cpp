#include "NumberLiteral.h"
#include <QJsonValue>

namespace Expression {

NumberLiteral::NumberLiteral(double literal, Node* parent) : Expression(parent), m_literal(literal) {

}

QJsonValue NumberLiteral::serializeToJson() const {
    return m_literal;
}

}
