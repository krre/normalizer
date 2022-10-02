#pragma once
#include "norm/expression/Expression.h"

namespace Expression {

class BooleanLiteral : public Expression {
public:
    BooleanLiteral(bool literal, Node* parent = nullptr);

    QJsonValue serializeToJson() const override;

private:
    bool m_literal;
};

}
