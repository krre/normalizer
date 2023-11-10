#include "HttpNetworkManager.h"
#include "core/async/NetworkAccessManager.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkReply>

HttpNetworkManager::HttpNetworkManager(const QString& host, quint16 port) : m_host(host), m_port(port) {
}

Async::Task<QString> HttpNetworkManager::createUser(const User& user) {
    QJsonObject data;
    data["login"] = user.login;
    data["full_name"] = user.fullName;
    data["email"] = user.email;
    data["password"] = user.password;

    QVariant response = co_await post("/users", data);
    co_return response.toMap()["token"].toString();
}

Async::Task<QString> HttpNetworkManager::login(const User& user) {
    QJsonObject data;
    data["email"] = user.email;
    data["password"] = user.password;

    QVariant response = co_await post("/users/login", data);
    co_return response.toMap()["token"].toString();
}

Async::Task<QVariant> HttpNetworkManager::post(const QString& endpoint, const QByteArray& data) {
    QUrl url;
    url.setScheme("http");
    url.setHost(m_host);
    url.setPath(endpoint);

    if (m_port) {
        url.setPort(m_port);
    }

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    Async::NetworkAccessManager networkAccessManager;
    QNetworkReply* reply = co_await networkAccessManager.post(request, data);

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray response = reply->readAll();
        co_return QJsonDocument::fromJson(response).toVariant();
    } else {
        throw NetworkException(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(), reply->errorString());
    }
}

Async::Task<QVariant> HttpNetworkManager::post(const QString& endpoint, const QJsonObject& data) {
    co_return co_await post(endpoint, QJsonDocument(data).toJson(QJsonDocument::Compact));
}
