#pragma once

namespace Expression::Operator {

class Expression;

class Math {
public:
    enum class Operation {
        Addition,
        Subtraction,
        Multiplication,
        Division
    };

    Math(Expression* expr1, Expression* expr2, Operation operation);

    Expression* expr1() const;
    Expression* expr2() const;

    Operation operation() const;

private:
    Expression* m_expr1;
    Expression* m_expr2;
    Operation m_operation;
};

}
