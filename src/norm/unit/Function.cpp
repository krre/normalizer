#include "Function.h"
#include "Parameter.h"
#include "Flow.h"
#include "project/Node.h"

namespace Unit {

Function::Function(Node* parent) : Unit(parent) {
    m_flow = new Flow(this);
}

Unit::Kind Function::kind() const {
    return Kind::Function;
}

const Parameters& Function::parameters() const {
    return m_parameters;
}

void Function::setParameters(const Parameters& parameters) {
    m_parameters = parameters;
}

Flow* Function::flow() const {
    return m_flow;
}

}
