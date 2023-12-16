#pragma once
#include <QUrl>

class Settings {
public:
    struct MainWindow {
        QByteArray geometry;
        QByteArray state;
    };

    struct Server {
        QUrl url;
    };

    struct Account {
        QString token;
    };

    virtual void setMainWindow(const MainWindow& mainWindow) = 0;
    virtual MainWindow mainWindow() const = 0;
    virtual bool containsGeometry() const = 0;

    virtual void setServer(const Server& server) = 0;
    virtual Server server() const = 0;

    virtual void setAccount(const Account& account) = 0;
    virtual Account account() const = 0;
};
