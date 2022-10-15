#pragma once
#include "norm/Token.h"

namespace Norm {

class Parameter;

class Function : public Token {
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
