#include "Math.h"

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

}
