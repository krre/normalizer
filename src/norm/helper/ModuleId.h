#pragma once
#include "Helper.h"
#include "core/CommonTypes.h"

namespace Norm::Helper {

class ModuleId : public Helper {
public:
    ModuleId();

    void serialize(QDataStream& stream) const override;
    void deserialize(QDataStream& stream) override;

    void setModuleId(Id moduleId);
    Id moduleId() const;

private:
    Id m_moduleId;
};

}
