#pragma once
#include <QtGlobal>
#include <QString>

namespace Type {

class Type {
public:
    using Id = quint32;

    Type();

    Id id() const;

    QString name() const;
    void setName(const QString& name);

private:
    Id m_id = 0;
    QString m_name;
};

}
