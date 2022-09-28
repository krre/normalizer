#include "Parameter.h"

namespace Unit {

Parameter::Parameter(DataType type, const QVariant& data) : m_dataType(type), m_data(data) {

}

DataType Parameter::dataType() const {
    return m_dataType;
}

void Parameter::setDataType(const DataType& dataType) {
    m_dataType = dataType;
}

QVariant Parameter::data() const {
    return m_data;
}

void Parameter::setData(const QVariant& data) {
    m_data = data;
}

}
