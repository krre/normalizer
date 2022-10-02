#pragma once
#include "norm/expression/Expression.h"
#include <QString>

namespace Expression {

class StringLiteral : public Expression {
public:
    StringLiteral(const QString& literal, Node* parent = nullptr);

    QJsonValue serializeToJson() const override;

private:
    QString m_literal;
};

}
