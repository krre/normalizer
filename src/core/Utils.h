#pragma once
#include <QString>

class Utils {
public:
    Utils();

    static QString applicationPath(const QString& projectPath);
    static QString libraryPath(const QString& projectPath);
};
