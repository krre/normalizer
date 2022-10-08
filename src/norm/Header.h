#pragma once
#include "Token.h"
#include <QVersionNumber>

class Header : public Token  {
public:
    Header();
    Type type() const override;

    void setVersion(const QVersionNumber& version);
    QVersionNumber version() const;

protected:
    QByteArray serialize() const override;
    void deserialize(const QByteArray& data) override;

private:
    QVersionNumber m_version;
};
