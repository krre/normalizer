#pragma once
#include "core/async/Task.h"
#include <QString>

class NetworkException : public std::exception {
public:
    NetworkException(int status, const QString& message = QString()) : m_status(status), m_message(message) {}

    int status() const { return m_status; }
    QString message() const { return m_message; }

private:
    int m_status = 0;
    QString m_message;
};

class AbstractNetworkManager {
public:
    struct User {
        QString sign;
        QString name;
        QString email;
        QString password;
    };

    virtual Async::Task<QString> registerUser(const QString& url, const User& user) = 0;
};
