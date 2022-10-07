#pragma once
#include "norm/expression/Expression.h"

namespace Expression::Operator {

class Operator : public Expression {
public:
    Operator(Node* parent = nullptr);
};

}
