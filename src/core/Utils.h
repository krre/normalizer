#pragma once
#include <QString>

class Utils {
public:
    Utils();
    static QString sha256(const QString& data);
};
