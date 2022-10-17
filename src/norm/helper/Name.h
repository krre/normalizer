#pragma once
#include "Helper.h"
#include "norm/Token.h"

namespace Norm::Helper {

class Name : public Helper {
public:
    Name();

    void serialize(QDataStream& stream) const override;
    void deserialize(QDataStream& stream) override;

    QString name() const;
    void setName(const QString& name);

private:
    QString m_name = "Unnamed";
};

}
