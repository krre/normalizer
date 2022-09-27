#pragma once
#include "Helper.h"
#include <QString>

namespace Unit::Helper {

class Name : Helper {
public:
    Name();

    QString name() const;
    void setName(const QString& name);

private:
    QString m_name = "Unnamed";
};

}
