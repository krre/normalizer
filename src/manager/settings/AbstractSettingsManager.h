#pragma once
#include <QString>

class AbstractSettingsManager {
public:
    struct ServerAddress {
        QString host;
        quint16 port;
    };

    struct Account {
        QString token;
    };

    virtual void setServerAddress(const ServerAddress& serverAddress) = 0;
    virtual ServerAddress serverAddress() const = 0;

    virtual void setAccount(const Account& account) = 0;
    virtual Account account() const = 0;
};
