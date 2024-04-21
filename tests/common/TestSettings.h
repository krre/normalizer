#include "external/settings/Settings.h"

class TestSettings : public Settings {
public:
    void setMainWindow(const MainWindow& mainWindow [[maybe_unused]]) override {}
    Settings::MainWindow mainWindow() const override;

    void setAccount(const Account& account) override;
    Account account() const override;

    void setDevelopmentServer(const DevelopmentServer& developmentServer) override;
    DevelopmentServer developmentServer() const override;

    void setProjectTable(const ProjectTable& projectTable) override;
    ProjectTable projectTable() const override;

    void setEditor(const Editor& editor) override;
    Editor editor() const override;

private:
    Account m_account;
    DevelopmentServer m_developmentServer;
    ProjectTable m_projectTable;
    Editor m_editor;
};
