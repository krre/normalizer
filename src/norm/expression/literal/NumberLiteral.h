#pragma once
#include "norm/expression/Expression.h"

namespace Norm {

class NumberLiteral : public Expression {
public:
    NumberLiteral();

    Code code() const override;

    void serialize(QDataStream& stream) const override;
    void deserialize(QDataStream& stream) override;

    void setLiteral(double literal);
    double literal() const;

private:
    double m_literal;
};

}
