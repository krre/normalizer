#include "StringLiteral.h"
#include <QJsonValue>

namespace Expression {

StringLiteral::StringLiteral(const QString& literal, Node* parent) : Expression(parent), m_literal(literal) {

}

QJsonValue StringLiteral::serializeToJson() const {
    return m_literal;
}

}
