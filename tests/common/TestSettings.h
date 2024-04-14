#include "external/settings/Settings.h"

class TestSettings : public Settings {
public:
    void setMainWindow(const MainWindow& mainWindow [[maybe_unused]]) override {}
    Settings::MainWindow mainWindow() const override;

    void setAccount(const Account& account) override;
    Account account() const override;

    void setNormHost(const NormHost& normHost) override;
    NormHost normHost() const override;

    void setProjectTable(const ProjectTable& projectTable) override;
    ProjectTable projectTable() const override;

    void setEditor(const Editor& editor) override;
    Editor editor() const override;

private:
    Account m_account;
    NormHost m_normHost;
    ProjectTable m_projectTable;
    Editor m_editor;
};
