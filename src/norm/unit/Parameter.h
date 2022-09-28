#pragma once
#include "Unit.h"
#include "helper/Name.h"
#include "norm/DataType.h"
#include <QVariant>

namespace Unit {

class Parameter : public Unit, public Helper::Name {
public:
    Parameter(DataType type, const QVariant& data);

    DataType dataType() const;
    void setDataType(const DataType& dataType);

    QVariant data() const;
    void setData(const QVariant& data);

private:
    DataType m_dataType;
    QVariant m_data;
};

}
