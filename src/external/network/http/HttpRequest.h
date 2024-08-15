#pragma once
#include "core/async/Task.h"
#include <QUrlQuery>
#include <QVariant>

class QNetworkReply;
class QNetworkRequest;

namespace Async {
    class NetworkAccessManager;
}

class HttpRequestAttributes;

class HttpRequest {
public:
    HttpRequest(Async::NetworkAccessManager* networkAccessManager, HttpRequestAttributes* requestAttributes);
    Async::Task<QVariant> send(const QString& endpoint);

protected:
    virtual Async::Task<QNetworkReply*> sendRequest(Async::NetworkAccessManager* networkAccessManager, QNetworkRequest* request) = 0;

private:
    Async::NetworkAccessManager* m_networkAccessManager = nullptr;
    HttpRequestAttributes* m_requestAttributes = nullptr;
};

class GetHttpRequest : public HttpRequest {
public:
    GetHttpRequest(Async::NetworkAccessManager* networkAccessManager, HttpRequestAttributes* requestAttributes, const QUrlQuery& query = QUrlQuery());

protected:
    Async::Task<QNetworkReply*> sendRequest(Async::NetworkAccessManager* networkAccessManager, QNetworkRequest* request) override;

private:
    QUrlQuery m_query;
};

class PostHttpRequest : public HttpRequest {
public:
    PostHttpRequest(Async::NetworkAccessManager* networkAccessManager, HttpRequestAttributes* requestAttributes, const QVariant& data = QVariant());

protected:
    Async::Task<QNetworkReply*> sendRequest(Async::NetworkAccessManager* networkAccessManager, QNetworkRequest* request) override;

private:
    QVariant m_data;
};

class PutHttpRequest : public HttpRequest {
public:
    PutHttpRequest(Async::NetworkAccessManager* networkAccessManager, HttpRequestAttributes* requestAttributes, const QVariant& data = QVariant());

protected:
    Async::Task<QNetworkReply*> sendRequest(Async::NetworkAccessManager* networkAccessManager, QNetworkRequest* request) override;

private:
    QVariant m_data;
};

class DeleteHttpRequest : public HttpRequest {
public:
    DeleteHttpRequest(Async::NetworkAccessManager* networkAccessManager, HttpRequestAttributes* requestAttributes);

protected:
    Async::Task<QNetworkReply*> sendRequest(Async::NetworkAccessManager* networkAccessManager, QNetworkRequest* request) override;
};
