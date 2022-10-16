#pragma once
#include "Helper.h"
#include "norm/Token.h"

namespace Norm::Helper {

class NameId : public Helper {
public:
    NameId();

    void serialize(QDataStream& stream) const override;
    void deserialize(QDataStream& stream) override;

    void setNameId(Id nameId);
    Id nameId() const;

private:
    Id m_nameId;
};

}
