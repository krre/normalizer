#pragma once
#include "core/CommonTypes.h"
#include <QHash>
#include <functional>

namespace Norm {
    class Token;
}

class TokenFactory {
public:
    using CreatorFunc = std::function<Norm::Token*()>;

    TokenFactory();
    Norm::Token* create(Norm::Code code);

private:
    QHash<Norm::Code, CreatorFunc> creators;
};
