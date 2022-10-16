#include "Math.h"
#include "core/Constants.h"

namespace Norm {

Math::Math() {
}

Math::Operation Math::operation() const {
    return m_operation;
}

void Math::setOperation(Operation operation) {
    m_operation = operation;
}

Code Math::code() const {
    return Const::Norm::Token::Math;
}

void Math::serialize(QDataStream& stream) const {
    stream << (quint8)(m_operation);
}

void Math::deserialize(QDataStream& stream) {
    stream >> m_operation;
}

}
