#pragma once
#include "norm/Token.h"

namespace Norm::Helper {

class ModuleId {
public:
    ModuleId();

    void setModuleId(Token::Id moduleId);
    Token::Id moduleId() const;

private:
    Token::Id m_module_id;
};

}
