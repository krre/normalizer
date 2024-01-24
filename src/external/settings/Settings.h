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
    };

    struct Account {
        QString token;
    };

    struct Project {
        Id id;
        QString name;
    };

    struct ProjectTable {
        QByteArray header;
    };

    struct Editor {
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

    virtual void setProjectTable(const ProjectTable& projectTable) = 0;
    virtual ProjectTable projectTable() const = 0;

    virtual void setEditor(const Editor& editor) = 0;
    virtual Editor editor() const = 0;
};
