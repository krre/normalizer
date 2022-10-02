#include "Math.h"
#include <QJsonObject>
#include <QJsonArray>

namespace Expression::Operator {

Math::Math(Operation operation, const Expressions& expressions, Node* parent) : Expression(parent), m_operation(operation), m_expressions(expressions) {
    for (auto expression : expressions) {
        expression->setParent(this);
    }
}

Math::Operation Math::operation() const {
    return m_operation;
}

const Expressions& Math::expressions() const {
    return m_expressions;
}

QJsonValue Math::serializeToJson() const {
    QJsonObject result = Expression::serializeToJson().toObject();
    result["op"] = int(m_operation);

    QJsonArray expressions;

    for (auto expression : m_expressions) {
        expressions.append(expression->serializeToJson());
    }

    result["expressions"] = expressions;

    return result;
}

}
