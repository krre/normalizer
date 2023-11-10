#pragma once
#include "NetworkManager.h"
#include "HttpRequestAttributes.h"
#include "core/async/NetworkAccessManager.h"
#include <QJsonObject>
#include <QUrlQuery>

class HttpNetworkManager : public NetworkManager {
public:
    HttpNetworkManager(const QString& host, quint16 port = 0);

    void setToken(const QString& token);

    Async::Task<QString> createUser(const User& user) override;
    Async::Task<User> getUser() override;
    Async::Task<QString> login(const User& user) override;

private:
    Async::Task<QVariant> get(const QString& endpoint, const QUrlQuery& query = QUrlQuery());

    Async::Task<QVariant> post(const QString& endpoint, const QByteArray& data = QByteArray());
    Async::Task<QVariant> post(const QString& endpoint, const QJsonObject& data = QJsonObject());

    Async::NetworkAccessManager m_networkAccessManager;
    HttpRequestAttributes m_requestAttributes;
};
