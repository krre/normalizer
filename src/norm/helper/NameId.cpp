#include "NameId.h"
#include <QDataStream>

namespace Norm::Helper {

NameId::NameId() {

}

void NameId::serialize(QDataStream& stream) const {
    stream << m_nameId;
}

void NameId::deserialize(QDataStream& stream) {
    stream >> m_nameId;
}

void NameId::setNameId(Id moduleId) {
    m_nameId = moduleId;
}

Id NameId::nameId() const {
    return m_nameId;
}

}
