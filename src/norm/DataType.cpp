#include "DataType.h"

DataType::DataType() {

}

DataType::Id DataType::id() const {
    return m_id;
}

QString DataType::name() const {
    return m_name;
}

void DataType::setName(const QString& name) {
    m_name = name;
}
