#pragma once
#include "norm/expression/Expression.h"

namespace Norm {

class BooleanLiteral : public Expression {
public:
    BooleanLiteral(bool literal);

private:
    bool m_literal;
};

}
