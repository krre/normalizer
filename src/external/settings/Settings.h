#pragma once
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

    struct ProjectLocation {
        QString workspace;
        QString host;
    };

    struct NormLocation {
        enum class Type {
            Home,
            Custom
        };

        Type type;
        QString directory;
    };

    struct ProjectTable {
        QByteArray geometry;
        QByteArray header;
    };

    struct Editor {
        int selected;
    };

    virtual void setMainWindow(const MainWindow& mainWindow) = 0;
    virtual MainWindow mainWindow() const = 0;

    virtual void setAccount(const Account& account) = 0;
    virtual Account account() const = 0;

    virtual void setProjectLocation(const ProjectLocation& projectLocation) = 0;
    virtual ProjectLocation projectLocation() const = 0;

    virtual void setNormLocation(const NormLocation& normLocation) = 0;
    virtual NormLocation normLocation() const = 0;

    virtual void setProjectTable(const ProjectTable& projectTable) = 0;
    virtual ProjectTable projectTable() const = 0;

    virtual void setEditor(const Editor& editor) = 0;
    virtual Editor editor() const = 0;
};
