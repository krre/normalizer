#pragma once
#include "core/async/Task.h"
#include <QUrlQuery>
#include <QVariant>

namespace RestStatus {
    constexpr auto BadRequest = 400;
    constexpr auto Unauthorized = 401;
    constexpr auto NotFound = 404;
    constexpr auto Conflict = 409;
}

class RestException : public std::exception {
public:
    RestException(int status, const QString& message = QString()) : m_status(status), m_message(message) {}

    int status() const { return m_status; }
    QString message() const { return m_message; }

private:
    int m_status = 0;
    QString m_message;
};

class RestApi {
public:
    virtual Async::Task<QVariant> get(const QString& endpoint, const QUrlQuery& query = QUrlQuery()) = 0;
    virtual Async::Task<QVariant> del(const QString& endpoint) = 0;
    virtual Async::Task<QVariant> post(const QString& endpoint, const QVariant& data = QVariant()) = 0;
    virtual Async::Task<QVariant> put(const QString& endpoint, const QVariant& data = QVariant()) = 0;
};
