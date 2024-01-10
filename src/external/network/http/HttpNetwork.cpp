#include "HttpNetwork.h"
#include "HttpRequest.h"
#include <QNetworkReply>

HttpNetwork::HttpNetwork(const QUrl& url) {
    setUrl(url);
}

void HttpNetwork::setUrl(const QUrl& url) {
    m_requestAttributes.url = url;
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

Async::Task<QVariant> HttpNetwork::post(const QString& endpoint, const QVariant& data) {
    PostHttpRequest httpRequest(&m_networkAccessManager, &m_requestAttributes, data);
    co_return co_await httpRequest.send(endpoint);
}

Async::Task<QVariant> HttpNetwork::put(const QString& endpoint, const QVariant& data) {
    PutHttpRequest httpRequest(&m_networkAccessManager, &m_requestAttributes, data);
    co_return co_await httpRequest.send(endpoint);
}
