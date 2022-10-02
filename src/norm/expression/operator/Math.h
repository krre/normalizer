#pragma once
#include "norm/expression/Expression.h"

namespace Expression::Operator {

class Math : public Expression {
public:
    enum class Operation {
        Addition,
        Subtraction,
        Multiplication,
        Division
    };

    Math(Operation operation, const Expressions& expressions);

    Operation operation() const;
    const Expressions& expressions() const;

private:
    Operation m_operation;
    Expressions m_expressions;
};

}
