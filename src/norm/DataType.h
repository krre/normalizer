#pragma once
#include <QtGlobal>
#include <QString>

class DataType {
public:
    using Id = quint32;

    DataType();

    Id id() const;

    QString name() const;
    void setName(const QString& name);

private:
    Id m_id = 0;
    QString m_name;
};
