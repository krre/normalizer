#include "ModuleId.h"

namespace Norm::Helper {

ModuleId::ModuleId() {

}

void ModuleId::setModuleId(Token::Id moduleId) {
    m_module_id = moduleId;
}

Token::Id ModuleId::moduleId() const {
    return m_module_id;
}

}
