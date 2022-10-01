#pragma once
#include <QJsonObject>

namespace Unit {

class Unit {
public:
    using Id = qint64;

    enum class Kind {
        Project,
        Module,
        Interface,
        Function,
        Parameter,
        Expression,
        Condition,
        Loop,
        Operator,
        Constant,
        Variable,
        Structure,
        Field,
        Custom
    };

    Unit();

    virtual Kind kind() const = 0;

    Id id() const;
    void setId(Id id);

    QString comment() const;
    void setComment(const QString& comment);

    QJsonObject toJson() const;

    QByteArray toBinary() const;
    void fromBinary(const QByteArray& binary);

protected:
    virtual QJsonObject toJsonUnit() const = 0;

    virtual QByteArray toBinaryUnit() const = 0;
    virtual void fromBinaryUnit(const QByteArray& binary) = 0;

private:
    Id m_id = 0;
    QString m_comment;
};

}
