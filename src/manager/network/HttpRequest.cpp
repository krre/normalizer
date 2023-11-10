#include "HttpRequest.h"
#include "HttpRequestAttributes.h"
#include "NetworkManager.h"
#include "core/async/NetworkAccessManager.h"
#include <QNetworkReply>
#include <QJsonDocument>

HttpRequest::HttpRequest(Async::NetworkAccessManager* networkAccessManager, HttpRequestAttributes* requestAttributes) : m_networkAccessManager(networkAccessManager), m_requestAttributes(requestAttributes) {

}

Async::Task<QVariant> HttpRequest::send(const QString& endpoint) {
    QUrl url;
    url.setScheme(m_requestAttributes->scheme == HttpRequestAttributes::Scheme::Http ? "http" : "https");
    url.setHost(m_requestAttributes->host);
    url.setPath(endpoint);

    if (m_requestAttributes->port) {
        url.setPort(m_requestAttributes->port);
    }

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    if (!m_requestAttributes->token.isEmpty()) {
        request.setRawHeader("Authorization", m_requestAttributes->token.toUtf8());
    }

    QNetworkReply* reply = co_await sendRequest(m_networkAccessManager, &request);

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray response = reply->readAll();
        co_return QJsonDocument::fromJson(response).toVariant();
    } else {
        throw NetworkException(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(), reply->errorString());
    }
}

GetHttpRequest::GetHttpRequest(Async::NetworkAccessManager* networkAccessManager, HttpRequestAttributes* requestAttributes, const QUrlQuery& query) :
    HttpRequest(networkAccessManager, requestAttributes), m_query(query) {
}

Async::Task<QNetworkReply*> GetHttpRequest::sendRequest(Async::NetworkAccessManager* networkAccessManager, QNetworkRequest* request) {
    if (!m_query.isEmpty()) {
        QUrl url = request->url();
        url.setQuery(m_query);
    }

    co_return co_await networkAccessManager->get(*request);
}

PostHttpRequest::PostHttpRequest(Async::NetworkAccessManager* networkAccessManager, HttpRequestAttributes* requestAttributes, const QByteArray& data) :
    HttpRequest(networkAccessManager, requestAttributes), m_data(data) {
}

Async::Task<QNetworkReply*> PostHttpRequest::sendRequest(Async::NetworkAccessManager* networkAccessManager, QNetworkRequest* request) {
    co_return co_await networkAccessManager->post(*request, m_data);
}
