#pragma once
#include "norm/Token.h"
#include "norm/helper/TypeId.h"
#include "norm/helper/Name.h"
#include "norm/helper/FunctionId.h"

namespace Norm {

class Parameter : public Token, public Helper::Name, public Helper::TypeId, public Helper::FunctionId {
public:
    Parameter();
    Code code() const override;

    void serialize(QDataStream& stream) const override;
    void deserialize(QDataStream& stream) override;
};

}
