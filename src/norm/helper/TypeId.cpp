#include "TypeId.h"
#include <QDataStream>

namespace Norm::Helper {

TypeId::TypeId() {

}

void TypeId::serialize(QDataStream& stream) const {
    stream << m_typeId;
}

void TypeId::deserialize(QDataStream& stream) {
    stream >> m_typeId;
}

void TypeId::setTypeId(Id moduleId) {
    m_typeId = moduleId;
}

Id TypeId::typeId() const {
    return m_typeId;
}

}
