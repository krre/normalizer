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
    Token::serialize(stream);
    ModuleId::serialize(stream);
}

void Module::deserialize(QDataStream& stream) {
    Token::deserialize(stream);
    ModuleId::deserialize(stream);
}

}
