#pragma once
#include "Token.h"
#include <QVersionNumber>

class Header : public Token  {
public:
    Header();
    virtual ~Header();

    Type type() const override;

    void setVersion(const QVersionNumber& version);
    QVersionNumber version() const;

    void serialize(QDataStream& stream) const override;
    void deserialize(QDataStream& stream) override;

private:
    QVersionNumber m_version;
};
