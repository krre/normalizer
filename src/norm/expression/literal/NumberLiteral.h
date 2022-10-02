#pragma once
#include "norm/expression/Expression.h"

namespace Expression {

class NumberLiteral : public Expression {
public:
    NumberLiteral(double literal, Node* parent = nullptr);

    QJsonValue serializeToJson() const override;

private:
    double m_literal;
};

}
