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
    stream << m_parentId;
}

void Module::deserialize(QDataStream& stream) {
    Id nameId;
    stream >> nameId;

    Id parentId;
    stream >> parentId;
}

Token::Id Module::parentId() const {
    return m_parentId;
}

void Module::setParentId(Id parentId) {
    m_parentId = parentId;
}

}
