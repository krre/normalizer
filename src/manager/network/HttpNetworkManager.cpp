#include "HttpNetworkManager.h"
#include "core/async/NetworkAccessManager.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkReply>

HttpNetworkManager::HttpNetworkManager(const QString& host, quint16 port) : m_host(host), m_port(port) {
}

void HttpNetworkManager::setToken(const QString& token) {
    m_token = token;
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

Async::Task<NetworkManager::User> HttpNetworkManager::getUser() {
    QVariant response = co_await get("/user");
    QVariantMap params = response.toMap();

    User user;
    user.login = params["login"].toString();
    user.email = params["email"].toString();
    user.fullName = params["full_name"].toString();

    co_return user;
}

Async::Task<QString> HttpNetworkManager::login(const User& user) {
    QJsonObject data;
    data["email"] = user.email;
    data["password"] = user.password;

    QVariant response = co_await post("/users/login", data);
    co_return response.toMap()["token"].toString();
}

Async::Task<QVariant> HttpNetworkManager::get(const QString& endpoint, const QUrlQuery& query) {
    QUrl url;
    url.setScheme("http");
    url.setHost(m_host);
    url.setPath(endpoint);

    if (m_port) {
        url.setPort(m_port);
    }

    url.setQuery(query);

    QNetworkRequest request(url);

    if (!m_token.isEmpty()) {
        request.setRawHeader("Authorization", m_token.toUtf8());
    }

    Async::NetworkAccessManager networkAccessManager;
    QNetworkReply* reply = co_await networkAccessManager.get(request);

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray response = reply->readAll();
        co_return QJsonDocument::fromJson(response).toVariant();
    } else {
        throw NetworkException(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(), reply->errorString());
    }
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

    if (!m_token.isEmpty()) {
        request.setRawHeader("Authorization", m_token.toUtf8());
    }

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
