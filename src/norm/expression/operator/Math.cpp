#include "Math.h"

namespace Expression::Operator {

Math::Math(Expression* expr1, Expression* expr2, Operation operation) : m_expr1(expr1), m_expr2(expr2), m_operation(operation) {

}

Expression* Math::expr1() const {
    return m_expr1;
}

Expression* Math::expr2() const {
    return m_expr2;
}

Math::Operation Math::operation() const {
    return m_operation;
}

}
