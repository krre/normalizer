#pragma once
#include "Helper.h"
#include "norm/Token.h"

namespace Norm::Helper {

class NameId : public Helper {
public:
    NameId();

    void serialize(QDataStream& stream) const override;
    void deserialize(QDataStream& stream) override;

    void setNameId(Token::Id moduleId);
    Token::Id nameId() const;

private:
    Token::Id m_nameId;
};

}
