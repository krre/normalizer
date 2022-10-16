#include "Flow.h"
#include "core/Constants.h"

namespace Norm {

Flow::Flow() {

}

Code Flow::code() const {
    return Const::Norm::Token::Flow;
}

void Flow::addExpression(Id expressionId) {
    m_expressions.append(expressionId);
}

void Flow::insertExpression(int index, Id expressionId) {
    m_expressions.insert(index, expressionId);
}

void Flow::removeExpression(Id expressionId) {
    m_expressions.removeOne(expressionId);
}

void Flow::clearExpressions() {
    m_expressions.clear();
}

const Ids& Flow::expressions() const {
    return m_expressions;
}

}
