#pragma once
#include "NetworkManager.h"
#include <QHostAddress>

class HttpNetworkManager : public NetworkManager {
public:
    HttpNetworkManager(const QString& host, quint16 port = 0);

    Async::Task<QString> createUser(const User& user) override;
    Async::Task<QString> login(const User& user) override;

private:
    Async::Task<QVariant> post(const QString& endpoint, const QByteArray& data = QByteArray());

    QString m_host;
    quint16 m_port = 0;
};
