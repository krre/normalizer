#include "HttpNetworkManager.h"
#include "HttpRequest.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkReply>

HttpNetworkManager::HttpNetworkManager(const QString& host, quint16 port) {
    m_requestAttributes.scheme = HttpRequestAttributes::Scheme::Http;
    m_requestAttributes.host = host;
    m_requestAttributes.port = port;
}

void HttpNetworkManager::setToken(const QString& token) {
    m_requestAttributes.token = token;
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

Async::Task<void> HttpNetworkManager::updateUser(const User& user) {
    QJsonObject data;
    data["full_name"] = user.fullName;

    co_await put("/user", data);
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

Async::Task<void> HttpNetworkManager::deleteUser() {
    co_await deleteResource("/user");
}

Async::Task<void> HttpNetworkManager::changePassword(const UserPassword& userPassword) {
    QJsonObject data;
    data["old_password"] = userPassword.oldPassword;
    data["new_password"] = userPassword.newPassword;

    co_await put("/user/password", data);
}

Async::Task<QVariant> HttpNetworkManager::get(const QString& endpoint, const QUrlQuery& query) {
    GetHttpRequest httpRequest(&m_networkAccessManager, &m_requestAttributes, query);
    co_return co_await httpRequest.send(endpoint);
}

Async::Task<QVariant> HttpNetworkManager::deleteResource(const QString& endpoint) {
    DeleteHttpRequest httpRequest(&m_networkAccessManager, &m_requestAttributes);
    co_return co_await httpRequest.send(endpoint);
}

Async::Task<QVariant> HttpNetworkManager::post(const QString& endpoint, const QByteArray& data) {
    PostHttpRequest httpRequest(&m_networkAccessManager, &m_requestAttributes, data);
    co_return co_await httpRequest.send(endpoint);
}

Async::Task<QVariant> HttpNetworkManager::post(const QString& endpoint, const QJsonObject& data) {
    co_return co_await post(endpoint, QJsonDocument(data).toJson(QJsonDocument::Compact));
}

Async::Task<QVariant> HttpNetworkManager::put(const QString& endpoint, const QByteArray& data) {
    PutHttpRequest httpRequest(&m_networkAccessManager, &m_requestAttributes, data);
    co_return co_await httpRequest.send(endpoint);
}

Async::Task<QVariant> HttpNetworkManager::put(const QString& endpoint, const QJsonObject& data) {
    co_return co_await put(endpoint, QJsonDocument(data).toJson(QJsonDocument::Compact));
}
