#pragma once
#include "core/async/Task.h"
#include "core/async/NetworkAccessManager.h"
#include <QString>
#include <QJsonObject>
#include <QUrlQuery>

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

    struct UserPassword {
        QString oldPassword;
        QString newPassword;
    };

    virtual Async::Task<QString> createUser(const User& user) = 0;
    virtual Async::Task<void> updateUser(const User& user) = 0;
    virtual Async::Task<User> getUser() = 0;
    virtual Async::Task<QString> login(const User& user) = 0;
    virtual Async::Task<void> deleteUser() = 0;
    virtual Async::Task<void> changePassword(const UserPassword& userPassword) = 0;

    Async::Task<QVariant> get(const QString& endpoint, const QUrlQuery& query = QUrlQuery());
    Async::Task<QVariant> deleteResource(const QString& endpoint);

    Async::Task<QVariant> post(const QString& endpoint, const QByteArray& data = QByteArray());
    Async::Task<QVariant> post(const QString& endpoint, const QJsonObject& data = QJsonObject());

    Async::Task<QVariant> put(const QString& endpoint, const QByteArray& data = QByteArray());
    Async::Task<QVariant> put(const QString& endpoint, const QJsonObject& data = QJsonObject());

private:
    Async::NetworkAccessManager m_networkAccessManager;
};
