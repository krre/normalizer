#pragma once
#include "Token.h"

namespace Norm {

class Flow : public Token {
public:
    Flow();
    Code code() const override;
};

}
