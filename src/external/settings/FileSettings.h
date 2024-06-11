#pragma once
#include "Settings.h"

class FileSettings : public Settings {
public:
    FileSettings();

    void setMainWindow(const MainWindow& mainWindow) override;
    MainWindow mainWindow() const override;

    void setAccount(const Account& account) override;
    Account account() const override;

    void setDevelopmentServer(const DevelopmentServer& developmentServer) override;
    DevelopmentServer developmentServer() const override;

    void setProjectTable(const ProjectTable& projectTable) override;
    ProjectTable projectTable() const override;

    void setEditor(const Editor& editor) override;
    Editor editor() const override;

    void setGraphics(const Graphics& graphics) override;
    Graphics graphics() const override;
};
