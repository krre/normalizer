#pragma once
#include "HttpRequestAttributes.h"
#include "core/async/Task.h"
#include "core/async/NetworkAccessManager.h"
#include <QJsonObject>
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

class HttpNetwork {
public:
    HttpNetwork(const QUrl& url);

    void setToken(const QString& token);

    Async::Task<QVariant> get(const QString& endpoint, const QUrlQuery& query = QUrlQuery());
    Async::Task<QVariant> deleteResource(const QString& endpoint);

    Async::Task<QVariant> post(const QString& endpoint, const QByteArray& data = QByteArray());
    Async::Task<QVariant> post(const QString& endpoint, const QJsonObject& data = QJsonObject());

    Async::Task<QVariant> put(const QString& endpoint, const QByteArray& data = QByteArray());
    Async::Task<QVariant> put(const QString& endpoint, const QJsonObject& data = QJsonObject());

private:
    Async::NetworkAccessManager m_networkAccessManager;
    HttpRequestAttributes m_requestAttributes;
};
