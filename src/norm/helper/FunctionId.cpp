#include "FunctionId.h"
#include <QDataStream>

namespace Norm::Helper {

FunctionId::FunctionId() {

}

void FunctionId::serialize(QDataStream& stream) const {
    stream << m_functionId;
}

void FunctionId::deserialize(QDataStream& stream) {
    stream >> m_functionId;
}

void FunctionId::setFunctionId(Id functionId) {
    m_functionId = functionId;
}

Id FunctionId::functionId() const {
    return m_functionId;
}

}
