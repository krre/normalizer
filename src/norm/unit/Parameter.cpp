#include "Parameter.h"

namespace Unit {

Parameter::Parameter(DataType type) : m_dataType(type) {

}

Unit::Type Parameter::type() const {
    return Type::Parameter;
}

DataType Parameter::dataType() const {
    return m_dataType;
}

void Parameter::setDataType(const DataType& dataType) {
    m_dataType = dataType;
}

QJsonObject Parameter::toJsonUnit() const {
    QJsonObject result;
    result["name"] = name();
    result["dataType"] = m_dataType.name();

    return result;
}

QByteArray Parameter::toBinaryUnit() const {

}

void Parameter::fromBinaryUnit(const QByteArray& binary) {

}

}
