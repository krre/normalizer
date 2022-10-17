#pragma once
#include "norm/Token.h"
#include "norm/helper/ModuleId.h"
#include "norm/helper/Name.h"

namespace Norm {

class Parameter;

class Function : public Token, public Helper::Name, public Helper::ModuleId {
public:
    Function();

    Code code() const override;

    void serialize(QDataStream& stream) const override;
    void deserialize(QDataStream& stream) override;
};

}
