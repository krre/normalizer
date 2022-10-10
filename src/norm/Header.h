#pragma once
#include "Token.h"
#include <QVersionNumber>

namespace Norm {

class Header : public Token  {
public:
    Header();
    virtual ~Header();

    Type type() const override;

    void serialize(QDataStream& stream) const override;
    void deserialize(QDataStream& stream) override;

private:

};

}
