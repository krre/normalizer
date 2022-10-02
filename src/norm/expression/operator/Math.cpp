#include "Math.h"

namespace Expression::Operator {

Math::Math(Operation operation, const Expressions& expressions) : m_operation(operation), m_expressions(expressions) {

}

Math::Operation Math::operation() const {
    return m_operation;
}

const Expressions& Math::expressions() const {
    return m_expressions;
}

}
