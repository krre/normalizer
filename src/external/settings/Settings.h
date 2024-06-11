#pragma once
#include "core/Utils.h"
#include <QUrl>

class Settings {
public:
    struct MainWindow {
        QByteArray geometry;
        QByteArray state;
    };

    struct Account {
        QString token;
    };

    struct DevelopmentServer {
        QString url;
    };

    struct ProjectTable {
        QByteArray geometry;
        QByteArray header;
    };

    struct Editor {
        int selected;
        int projectId;
        QString projectName;
    };

    struct Graphics {
        int adapter;
    };

    virtual void setMainWindow(const MainWindow& mainWindow) = 0;
    virtual MainWindow mainWindow() const = 0;

    virtual void setAccount(const Account& account) = 0;
    virtual Account account() const = 0;

    virtual void setDevelopmentServer(const DevelopmentServer& developmentServer) = 0;
    virtual DevelopmentServer developmentServer() const = 0;

    virtual void setProjectTable(const ProjectTable& projectTable) = 0;
    virtual ProjectTable projectTable() const = 0;

    virtual void setEditor(const Editor& editor) = 0;
    virtual Editor editor() const = 0;

    virtual void setGraphics(const Graphics& graphics) = 0;
    virtual Graphics graphics() const = 0;
};
