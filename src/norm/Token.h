#pragma once
#include "TokenType.h"
#include <QObject>

namespace Norm {

class Token : public QObject {
public:
    virtual TokenType type() const = 0;

    void setId(TokenId id);
    TokenId id() const;

    QByteArray serialize() const;
    void parse(const QByteArray& data);

protected:
    virtual void getSerializedProperties(QDataStream& stream) const = 0;
    virtual void setParsedProperties(QDataStream& stream) = 0;

private:
    TokenId m_id = 0;
};

}
