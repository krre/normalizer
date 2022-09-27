#pragma once
#include "Unit.h"

class Function : public Unit {
public:
    Function();

public:
    Type type() const override;
    QString name() const override;

protected:
    QJsonObject toJsonUnit() const override;

    QByteArray toBinaryUnit() const override;
    void fromBinaryUnit(const QByteArray& binary) override;
};
