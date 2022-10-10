#pragma once
#include "norm/Token.h"

namespace Norm {

class Project : public Token {
public:
    Project();
    virtual ~Project();

    Type type() const override;

    void serialize(QDataStream& stream) const override;
    void deserialize(QDataStream& stream) override;
};

}
