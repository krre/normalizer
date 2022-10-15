#include "ModuleId.h"
#include <QDataStream>

namespace Norm::Helper {

ModuleId::ModuleId() {

}

void ModuleId::serialize(QDataStream& stream) const {
    stream << m_moduleId;
}

void ModuleId::deserialize(QDataStream& stream) {
    stream >> m_moduleId;
}

void ModuleId::setModuleId(Id moduleId) {
    m_moduleId = moduleId;
}

Id ModuleId::moduleId() const {
    return m_moduleId;
}

}
