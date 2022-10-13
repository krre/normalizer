#include "Module.h"
#include "Name.h"
#include "core/Constants.h"
#include <QDataStream>

namespace Norm {

Module::Module() {

}

Code Module::code() const {
    return Const::Norm::Token::Module;
}

void Module::serialize(QDataStream& stream) const {
    stream << name()->id();

    Id parentId = m_parent ? m_parent->id() : 0;
    stream << parentId;
}

void Module::deserialize(QDataStream& stream) {
    Id nameId;
    stream >> nameId;

    Id parentId;
    stream >> parentId;

    if (parentId) {

    }
}

Module* Module::parent() const {
    return m_parent;
}

void Module::setParent(Module* parent) {
    m_parent = parent;
}

}
