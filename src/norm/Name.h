#pragma once
#include "Token.h"

namespace Norm {

class Name : public Token {
public:
    Name();

    Code code() const override;

    void serialize(QDataStream& stream) const override;
    void deserialize(QDataStream& stream) override;

    QString name() const;
    void setName(const QString& name);

private:
    QString m_name = "Unnamed";
};

}
