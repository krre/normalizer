#pragma once
#include "norm/expression/Expression.h"

namespace Expression {

class NumberLiteral : public Expression {
public:
    NumberLiteral(double literal);

private:
    double m_literal;
};

}
