#pragma once
#include "norm/expression/Expression.h"
#include <QString>

namespace Norm {

class StringLiteral : public Expression {
public:
    StringLiteral(const QString& literal);

private:
    QString m_literal;
};

}
