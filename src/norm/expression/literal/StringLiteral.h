#pragma once
#include <QString>

namespace Expression {

class StringLiteral {
public:
    StringLiteral(const QString& literal);

private:
    QString m_literal;
};

}
