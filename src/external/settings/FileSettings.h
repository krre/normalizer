#pragma once
#include "Settings.h"

class FileSettings : public Settings {
public:
    FileSettings();

    void setMainWindow(const MainWindow& mainWindow) override;
    MainWindow mainWindow() const override;
    bool containsGeometry() const override;

    void setServer(const Server& server) override;
    Server server() const override;

    void setAccount(const Account& account) override;
    Account account() const override;

    void setProject(const Project& project) override;
    Project project() const override;

    void setNewProject(const NewProject& newProject) override;
    NewProject newProject() const override;

    void setProjectTable(const ProjectTable& projectTable) override;
    ProjectTable projectTable() const override;

    void setEditor(const Editor& editor) override;
    Editor editor() const override;
};
