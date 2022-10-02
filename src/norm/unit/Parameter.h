#pragma once
#include "Unit.h"
#include "helper/Name.h"
#include "norm/type/Type.h"
#include <QVariant>

namespace Unit {

class Parameter : public Unit, public Helper::Name {
public:
    Parameter(Type::Type type, Node* parent = nullptr);

    Kind kind() const override;

    Type::Type type() const;
    void setType(const Type::Type& type);

protected:
    QJsonObject toJsonUnit() const override;
    QByteArray toBinaryUnit() const override;
    void fromBinaryUnit(const QByteArray& binary) override;

private:
    Type::Type m_type;
};

}
