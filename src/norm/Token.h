#pragma once
#include <QtGlobal>

class Token {
public:
    enum class Type : quint8 {
        Header = 00
    };

    Token();
    virtual Type type() const = 0;

    void create(const QByteArray& data);
    QByteArray data() const;

protected:
    virtual QByteArray serialize() const = 0;
    virtual void deserialize(const QByteArray& data) = 0;
};
