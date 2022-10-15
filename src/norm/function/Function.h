#pragma once
#include "norm/Token.h"
#include "norm/helper/ModuleId.h"

namespace Norm {

class Parameter;

class Function : public Token, Helper::ModuleId {
public:
    Function();

    Code code() const override;

    void serialize(QDataStream& stream) const override;
    void deserialize(QDataStream& stream) override;

    void addParameter(Parameter* parameter);
    void removeParameter(Parameter* parameter);

private:
    QList<Parameter*> parameters;
};

}
