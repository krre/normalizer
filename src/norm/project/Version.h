#pragma once
#include "norm/Token.h"
#include <QVersionNumber>

namespace Norm {

class Version : public Token {
public:
    Version();

    Type type() const override;

    void setVersion(const QVersionNumber& version);
    QVersionNumber version() const;

    void serialize(QDataStream& stream) const override;
    void deserialize(QDataStream& stream) override;

private:
    QVersionNumber m_version;
};

}
