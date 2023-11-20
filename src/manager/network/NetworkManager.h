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

class NetworkManager {
public:
    struct User {
        QString login;
        QString fullName;
        QString email;
        QString password;
    };

    virtual Async::Task<QString> createUser(const User& user) = 0;
    virtual Async::Task<User> getUser() = 0;
    virtual Async::Task<QString> login(const User& user) = 0;
    virtual Async::Task<void> deleteUser() = 0;
};
