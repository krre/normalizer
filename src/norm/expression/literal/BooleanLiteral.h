#pragma once
#include "norm/expression/Expression.h"

namespace Norm {

class BooleanLiteral : public Expression {
public:
    BooleanLiteral();

    Code code() const override;

    void serialize(QDataStream& stream) const override;
    void deserialize(QDataStream& stream) override;

    void setLiteral(bool literal);
    bool literal() const;

private:
    bool m_literal;
};

}
