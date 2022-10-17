#pragma once
#include "Token.h"
#include "helper/Name.h"
#include "helper/ModuleId.h"
#include <QScopedPointer>

namespace Norm {

class Name;

class Module : public Token, public Helper::Name, public Helper::ModuleId {
public:
    Module();

    Code code() const override;

    void serialize(QDataStream& stream) const override;
    void deserialize(QDataStream& stream) override;
};

}
