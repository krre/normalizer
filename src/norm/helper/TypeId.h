#pragma once
#include "Helper.h"
#include "norm/Token.h"

namespace Norm::Helper {

class TypeId : public Helper {
public:
    TypeId();

    void serialize(QDataStream& stream) const override;
    void deserialize(QDataStream& stream) override;

    void setTypeId(Id moduleId);
    Id typeId() const;

private:
    Id m_typeId;
};

}
