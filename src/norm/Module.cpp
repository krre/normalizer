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
    stream << moduleId();
}

void Module::deserialize(QDataStream& stream) {
    Id moduleId;
    stream >> moduleId;
    setModuleId(moduleId);
}

}
