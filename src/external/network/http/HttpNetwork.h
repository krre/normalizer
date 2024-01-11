#pragma once
#include "HttpRequestAttributes.h"
#include "external/network/RestApi.h"
#include "core/async/Task.h"
#include "core/async/NetworkAccessManager.h"
#include <QUrlQuery>

class HttpException : public std::exception {
public:
    HttpException(int status, const QString& message = QString()) : m_status(status), m_message(message) {}

    int status() const { return m_status; }
    QString message() const { return m_message; }

private:
    int m_status = 0;
    QString m_message;
};

class HttpNetwork : public RestApi {
public:
    HttpNetwork(const QUrl& url);

    void setUrl(const QUrl& url);
    void setToken(const QString& token);

    Async::Task<QVariant> get(const QString& endpoint, const QUrlQuery& query = QUrlQuery()) override;
    Async::Task<QVariant> deleteResource(const QString& endpoint) override;
    Async::Task<QVariant> post(const QString& endpoint, const QVariant& data = QVariant()) override;
    Async::Task<QVariant> put(const QString& endpoint, const QVariant& data = QVariant()) override;

private:
    Async::NetworkAccessManager m_networkAccessManager;
    HttpRequestAttributes m_requestAttributes;
};
