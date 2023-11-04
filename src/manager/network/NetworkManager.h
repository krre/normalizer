#pragma once
#include "AbstractNetworkManager.h"
#include <QHostAddress>

class NetworkManager : public AbstractNetworkManager {
public:
    NetworkManager(const QHostAddress& address, quint16 port = 0);

    Async::Task<QString> registerUser(const User& user) override;

private:
    Async::Task<QVariant> post(const QString& endpoint, const QByteArray& data = QByteArray());

    QHostAddress m_address;
    quint16 m_port = 0;
};
