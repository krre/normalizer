#include "NetworkManager.h"
#include "core/async/NetworkAccessManager.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkReply>

NetworkManager::NetworkManager() {

}

Async::Task<QString> NetworkManager::registerUser(const QString& url, const User& user) {
    QJsonObject data;
    data["sign"] = user.sign;
    data["name"] = user.name;
    data["email"] = user.email;
    data["password"] = user.password;

    QNetworkRequest request(QUrl(url + "/users"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    Async::NetworkAccessManager networkAccessManager;
    QNetworkReply* reply = co_await networkAccessManager.post(request, QJsonDocument(data).toJson(QJsonDocument::Compact));

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray response = reply->readAll();
        co_return QJsonDocument::fromJson(response).object()["token"].toString();
    } else {
        throw NetworkException(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(), reply->errorString());
    }
}
