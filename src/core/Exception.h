#pragma once
#include "core/Format.h"
#include <QString>
#include <exception>

class Exception : std::exception {
public:
    Exception(const char* error);
    Exception(const QString& error);
    Exception(const std::string& error);

    // template<typename... Args>
    // Exception(std::format_string<Args...> fmt, Args&&... args) : Exception(std::format(fmt, args...)) {}

    const QString& error() const;

private:
    QString m_error;
};
