#pragma once
#include "norm/Token.h"
#include "norm/helper/ModuleId.h"
#include "norm/helper/NameId.h"

namespace Norm {

class Parameter;

class Function : public Token, Helper::NameId, Helper::ModuleId {
public:
    Function();

    Code code() const override;

    void serialize(QDataStream& stream) const override;
    void deserialize(QDataStream& stream) override;

    void addParameter(Id parameterId);
    void removeParameter(Id parameterId);

private:
    QList<Id> parameters;
};

}
