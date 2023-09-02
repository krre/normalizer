#pragma once
#include <QString>
#include <exception>

class Exception : std::exception {
public:
    Exception(const QString& error);
    const QString& error() const;

private:
    QString m_error;
};
