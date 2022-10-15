#pragma once
#include "norm/expression/Expression.h"

namespace Norm {

class Math : public Expression {
public:
    enum class Operation {
        Addition,
        Subtraction,
        Multiplication,
        Division
    };

    Math(Operation operation);

    Operation operation() const;

private:
    Operation m_operation;
};

}
