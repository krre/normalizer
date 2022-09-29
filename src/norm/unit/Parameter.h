#pragma once
#include "Unit.h"
#include "helper/Name.h"
#include "norm/DataType.h"
#include <QVariant>

namespace Unit {

class Parameter : public Unit, public Helper::Name {
public:
    Parameter(DataType type);

    Type type() const override;

    DataType dataType() const;
    void setDataType(const DataType& dataType);

protected:
    QJsonObject toJsonUnit() const override;
    QByteArray toBinaryUnit() const override;
    void fromBinaryUnit(const QByteArray& binary) override;

private:
    DataType m_dataType;
};

}
