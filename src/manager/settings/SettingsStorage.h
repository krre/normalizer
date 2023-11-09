#pragma once
#include <QString>

class SettingsStorage {
public:
    struct MainWindow {
        QByteArray geometry;
        QByteArray state;
    };

    struct ServerAddress {
        QString host;
        quint16 port;
    };

    struct Account {
        QString token;
    };

    virtual void setMainWindow(const MainWindow& mainWindow) = 0;
    virtual MainWindow mainWindow() const = 0;
    virtual bool containsMainWindow() const = 0;

    virtual void setServerAddress(const ServerAddress& serverAddress) = 0;
    virtual ServerAddress serverAddress() const = 0;

    virtual void setAccount(const Account& account) = 0;
    virtual Account account() const = 0;
};
