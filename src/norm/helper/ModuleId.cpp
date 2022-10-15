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

void ModuleId::setModuleId(Token::Id moduleId) {
    m_moduleId = moduleId;
}

Token::Id ModuleId::moduleId() const {
    return m_moduleId;
}

}
