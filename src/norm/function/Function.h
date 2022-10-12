#pragma once
#include "norm/Token.h"

namespace Norm {

class Function : public Token {
public:
    Function();

    void serialize(QDataStream& stream) const override;
    void deserialize(QDataStream& stream) override;
};

}
