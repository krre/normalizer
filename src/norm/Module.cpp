#include "Module.h"
#include "core/Constants.h"
#include <QDataStream>

namespace Norm {

Module::Module() {

}

Code Module::code() const {
    return Const::Norm::Token::Module;
}

void Module::serialize(QDataStream& stream) const {
    stream << m_moduleId;
}

void Module::deserialize(QDataStream& stream) {
    stream >> m_moduleId;
}

Token::Id Module::moduleId() const {
    return m_moduleId;
}

void Module::setModuleId(Id parentId) {
    m_moduleId = parentId;
}

}
