#include "HttpRequest.h"
#include "HttpRequestAttributes.h"
#include "external/network/http/HttpNetwork.h"
#include "core/async/NetworkAccessManager.h"
#include <QNetworkReply>
#include <QJsonDocument>

HttpRequest::HttpRequest(Async::NetworkAccessManager* networkAccessManager, HttpRequestAttributes* requestAttributes) : m_networkAccessManager(networkAccessManager), m_requestAttributes(requestAttributes) {

}

Async::Task<QVariant> HttpRequest::send(const QString& endpoint) {
    QUrl url = m_requestAttributes->url;
    url.setPath("/" + endpoint);

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    if (!m_requestAttributes->token.isEmpty()) {
        request.setRawHeader("Authorization", "Bearer " + m_requestAttributes->token.toUtf8());
    }

    QNetworkReply* reply = co_await sendRequest(m_networkAccessManager, &request);

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray response = reply->readAll();
        co_return QJsonDocument::fromJson(response).toVariant();
    } else {
        throw HttpException(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(), reply->errorString());
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

PostHttpRequest::PostHttpRequest(Async::NetworkAccessManager* networkAccessManager, HttpRequestAttributes* requestAttributes, const QVariant& data) :
    HttpRequest(networkAccessManager, requestAttributes), m_data(data) {
}

Async::Task<QNetworkReply*> PostHttpRequest::sendRequest(Async::NetworkAccessManager* networkAccessManager, QNetworkRequest* request) {
    co_return co_await networkAccessManager->post(*request, m_data.toByteArray());
}

PutHttpRequest::PutHttpRequest(Async::NetworkAccessManager* networkAccessManager, HttpRequestAttributes* requestAttributes, const QVariant& data) :
    HttpRequest(networkAccessManager, requestAttributes), m_data(data) {
}

Async::Task<QNetworkReply*> PutHttpRequest::sendRequest(Async::NetworkAccessManager* networkAccessManager, QNetworkRequest* request) {
    co_return co_await networkAccessManager->put(*request, m_data.toByteArray());
}

DeleteHttpRequest::DeleteHttpRequest(Async::NetworkAccessManager* networkAccessManager, HttpRequestAttributes* requestAttributes) :
    HttpRequest(networkAccessManager, requestAttributes) {
}

Async::Task<QNetworkReply*> DeleteHttpRequest::sendRequest(Async::NetworkAccessManager* networkAccessManager, QNetworkRequest* request) {
    co_return co_await networkAccessManager->deleteResource(*request);
}
