#pragma once
#include "Helper.h"
#include "norm/Token.h"

namespace Norm::Helper {

class ModuleId : public Helper {
public:
    ModuleId();

    void serialize(QDataStream& stream) const override;
    void deserialize(QDataStream& stream) override;

    void setModuleId(Token::Id moduleId);
    Token::Id moduleId() const;

private:
    Token::Id m_moduleId;
};

}
