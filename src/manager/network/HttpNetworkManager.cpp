#include "HttpNetworkManager.h"
#include "core/async/NetworkAccessManager.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkReply>

HttpNetworkManager::HttpNetworkManager(const QString& host, quint16 port) : m_host(host), m_port(port) {
}

Async::Task<QString> HttpNetworkManager::registerUser(const User& user) {
    QJsonObject data;
    data["sign"] = user.sign;
    data["name"] = user.name;
    data["email"] = user.email;
    data["password"] = user.password;

    QVariant response = co_await post("/users", QJsonDocument(data).toJson(QJsonDocument::Compact));
    co_return response.toMap()["token"].toString();
}

Async::Task<QVariant> HttpNetworkManager::post(const QString& endpoint, const QByteArray& data) {
    QString url = m_host;

    if (m_port) {
        url += ":" + QString::number(m_port);
    }

    QNetworkRequest request(QUrl(url + endpoint));
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
