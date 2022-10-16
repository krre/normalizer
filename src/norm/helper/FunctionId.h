#pragma once
#include "Helper.h"
#include "norm/Token.h"

namespace Norm::Helper {

class FunctionId : public Helper {
public:
    FunctionId();

    void serialize(QDataStream& stream) const override;
    void deserialize(QDataStream& stream) override;

    void setFunctionId(Id functionId);
    Id functionId() const;

private:
    Id m_functionId;
};

}
