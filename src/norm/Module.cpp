#include "Module.h"
#include "Name.h"
#include <QDataStream>

namespace Norm {

Module::Module() {

}

void Module::serialize(QDataStream& stream) const {
    stream << m_name->id();

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

Name* Module::name() const {
    return m_name.data();
}

void Module::setName(Name* name) {
    m_name.reset(name);
}

Module* Module::parent() const {
    return m_parent;
}

void Module::setParent(Module* parent) {
    m_parent = parent;
}

}
