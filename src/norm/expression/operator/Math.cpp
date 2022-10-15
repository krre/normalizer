#include "Math.h"

namespace Norm {

Math::Math(Operation operation) :  m_operation(operation) {
}

Math::Operation Math::operation() const {
    return m_operation;
}

}
