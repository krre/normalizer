#pragma once
#include "Helper.h"
#include "norm/Token.h"

namespace Norm::Helper {

class ExpressionId : public Helper {
public:
    ExpressionId();

    void serialize(QDataStream& stream) const override;
    void deserialize(QDataStream& stream) override;

    void setExpressionId(Id expressionId);
    Id expressionId() const;

private:
    Id m_expressionId;
};

}
