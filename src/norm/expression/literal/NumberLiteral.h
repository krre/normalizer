#pragma once

namespace Expression {

class NumberLiteral {
public:
    NumberLiteral(double literal);

private:
    double m_literal;
};

}
