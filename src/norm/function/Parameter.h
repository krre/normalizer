#pragma once
#include "norm/Token.h"
#include "norm/helper/TypeId.h"
#include "norm/helper/NameId.h"

namespace Norm {

class Parameter : public Token, public Helper::NameId, public Helper::TypeId {
public:
    Parameter();
    Code code() const override;

    void serialize(QDataStream& stream) const override;
    void deserialize(QDataStream& stream) override;
};

}
