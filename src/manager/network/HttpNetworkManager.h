#pragma once
#include "NetworkManager.h"
#include <QJsonObject>
#include <QUrlQuery>

class HttpNetworkManager : public NetworkManager {
public:
    HttpNetworkManager(const QString& host, quint16 port = 0);

    Async::Task<QString> createUser(const User& user) override;
    Async::Task<User> getUser() override;
    Async::Task<QString> login(const User& user) override;

private:
    Async::Task<QVariant> get(const QString& endpoint, const QUrlQuery& query = QUrlQuery());

    Async::Task<QVariant> post(const QString& endpoint, const QByteArray& data = QByteArray());
    Async::Task<QVariant> post(const QString& endpoint, const QJsonObject& data = QJsonObject());

    QString m_host;
    quint16 m_port = 0;
};
