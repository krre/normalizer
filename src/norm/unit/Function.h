#pragma once
#include "Unit.h"
#include "helper/Name.h"

namespace Unit {

class Function : public Unit, public Helper::Name {
public:
    Function();

public:
    Type type() const override;

protected:
    QJsonObject toJsonUnit() const override;

    QByteArray toBinaryUnit() const override;
    void fromBinaryUnit(const QByteArray& binary) override;
};

}
