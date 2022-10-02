#pragma once

namespace Expression {

class BooleanLiteral {
public:
    BooleanLiteral(bool literal);

private:
    bool m_literal;
};

}
