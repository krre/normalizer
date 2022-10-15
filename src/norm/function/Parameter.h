#pragma once
#include "norm/Token.h"
#include "norm/type/Type.h"

namespace Norm {

class Parameter : public Token {
public:
    Parameter();

    Type* type() const;
    void setType(Type* type);

private:
    Type* m_type;
};

}
