#pragma once
#include "norm/Token.h"

namespace Norm {

class Function : public Token {
public:
    Function();

    Code code() const override;

    void serialize(QDataStream& stream) const override;
    void deserialize(QDataStream& stream) override;
};

}
