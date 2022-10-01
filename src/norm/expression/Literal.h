#pragma once
#include <QVariant>

namespace Expression {

class Literal {
public:
    enum class Kind {
        Boolean,
        Number,
        String
    };

    Literal(bool literal);
    Literal(const QString& literal);
    Literal(double literal);

    QVariant literal() const;
    Kind kind() const;

private:
    QVariant m_literal;
    Kind m_kind;
};

}
