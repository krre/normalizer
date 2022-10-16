#pragma once
#include "Token.h"

namespace Norm {

class Flow : public Token {
public:
    Flow();
    Code code() const override;

    void addExpression(Id expressionId);
    void insertExpression(int index, Id expressionId);
    void removeExpression(Id expressionId);
    void clearExpressions();
    const Ids& expressions() const;

private:
    Ids m_expressions;
};

}
