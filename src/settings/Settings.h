#pragma once
#include "core/CommonTypes.h"
#include <QUrl>

class Settings {
public:
    struct MainWindow {
        QByteArray geometry;
        QByteArray state;
    };

    struct Server {
        QUrl api;
        QUrl editor;
    };

    struct Account {
        QString token;
    };

    struct Project {
        Id id;
        QString name;
    };

    struct View {
        int selected;
    };

    virtual void setMainWindow(const MainWindow& mainWindow) = 0;
    virtual MainWindow mainWindow() const = 0;
    virtual bool containsGeometry() const = 0;

    virtual void setServer(const Server& server) = 0;
    virtual Server server() const = 0;

    virtual void setAccount(const Account& account) = 0;
    virtual Account account() const = 0;

    virtual void setProject(const Project& project) = 0;
    virtual Project project() const = 0;

    virtual void setView(const View& view) = 0;
    virtual View view() const = 0;
};
