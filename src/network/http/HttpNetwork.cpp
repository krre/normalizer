#include "HttpNetwork.h"
#include "HttpRequest.h"
#include <QNetworkReply>
#include <QJsonDocument>

HttpNetwork::HttpNetwork(const QString& host, quint16 port) {
    m_requestAttributes.scheme = HttpRequestAttributes::Scheme::Http;
    m_requestAttributes.host = host;
    m_requestAttributes.port = port;
}

void HttpNetwork::setToken(const QString& token) {
    m_requestAttributes.token = token;
}

Async::Task<QVariant> HttpNetwork::get(const QString& endpoint, const QUrlQuery& query) {
    GetHttpRequest httpRequest(&m_networkAccessManager, &m_requestAttributes, query);
    co_return co_await httpRequest.send(endpoint);
}

Async::Task<QVariant> HttpNetwork::deleteResource(const QString& endpoint) {
    DeleteHttpRequest httpRequest(&m_networkAccessManager, &m_requestAttributes);
    co_return co_await httpRequest.send(endpoint);
}

Async::Task<QVariant> HttpNetwork::post(const QString& endpoint, const QByteArray& data) {
    PostHttpRequest httpRequest(&m_networkAccessManager, &m_requestAttributes, data);
    co_return co_await httpRequest.send(endpoint);
}

Async::Task<QVariant> HttpNetwork::post(const QString& endpoint, const QJsonObject& data) {
    co_return co_await post(endpoint, QJsonDocument(data).toJson(QJsonDocument::Compact));
}

Async::Task<QVariant> HttpNetwork::put(const QString& endpoint, const QByteArray& data) {
    PutHttpRequest httpRequest(&m_networkAccessManager, &m_requestAttributes, data);
    co_return co_await httpRequest.send(endpoint);
}

Async::Task<QVariant> HttpNetwork::put(const QString& endpoint, const QJsonObject& data) {
    co_return co_await put(endpoint, QJsonDocument(data).toJson(QJsonDocument::Compact));
}
