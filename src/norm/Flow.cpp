#include "Flow.h"
#include "core/Constants.h"

namespace Norm {

Flow::Flow() {

}

Code Flow::code() const {
    return Const::Norm::Token::Flow;
}

}
