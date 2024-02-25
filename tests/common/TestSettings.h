#include "external/settings/Settings.h"

class TestSettings : public Settings {
public:
    void setMainWindow(const MainWindow& mainWindow [[maybe_unused]]) override {}
    Settings::MainWindow mainWindow() const override;

    void setAccount(const Account& account) override;
    Account account() const override;

    void setProjectLocation(const ProjectLocation& projectLocation) override;
    ProjectLocation projectLocation() const override;

    void setNormLocation(const NormLocation& normLocation) override;
    NormLocation normLocation() const override;

    void setProjectTable(const ProjectTable& projectTable) override;
    ProjectTable projectTable() const override;

    void setEditor(const Editor& editor) override;
    Editor editor() const override;

private:
    Account m_account;
    ProjectLocation m_projectLocation;
    NormLocation m_normLocation;
    ProjectTable m_projectTable;
    Editor m_editor;
};
