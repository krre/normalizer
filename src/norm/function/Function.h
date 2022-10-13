#pragma once
#include "norm/helper/Name.h"
#include "norm/Token.h"

namespace Norm {

class Function : public Token, Helper::Name {
public:
    Function();

    Code code() const override;

    void serialize(QDataStream& stream) const override;
    void deserialize(QDataStream& stream) override;
};

}
