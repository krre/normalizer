#include "HttpRestApi.h"
#include "HttpRequest.h"
#include <QNetworkReply>

HttpRestApi::HttpRestApi(const QUrl& url) {
    setUrl(url);
}

void HttpRestApi::setUrl(const QUrl& url) {
    m_requestAttributes.url = url;
}

void HttpRestApi::setToken(const QString& token) {
    m_requestAttributes.token = token;
}

Async::Task<QVariant> HttpRestApi::get(const QString& endpoint, const QUrlQuery& query) {
    GetHttpRequest httpRequest(&m_networkAccessManager, &m_requestAttributes, query);
    co_return co_await httpRequest.send(endpoint);
}

Async::Task<QVariant> HttpRestApi::del(const QString& endpoint) {
    DeleteHttpRequest httpRequest(&m_networkAccessManager, &m_requestAttributes);
    co_return co_await httpRequest.send(endpoint);
}

Async::Task<QVariant> HttpRestApi::post(const QString& endpoint, const QVariant& data) {
    PostHttpRequest httpRequest(&m_networkAccessManager, &m_requestAttributes, data);
    co_return co_await httpRequest.send(endpoint);
}

Async::Task<QVariant> HttpRestApi::put(const QString& endpoint, const QVariant& data) {
    PutHttpRequest httpRequest(&m_networkAccessManager, &m_requestAttributes, data);
    co_return co_await httpRequest.send(endpoint);
}
