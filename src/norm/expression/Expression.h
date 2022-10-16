#pragma once
#include "norm/Token.h"
#include "norm/helper/FunctionId.h"

namespace Norm {

class Expression : public Token, public Helper::FunctionId {
public:
    Expression();

    void serialize(QDataStream& stream) const override;
    void deserialize(QDataStream& stream) override;
};

}
