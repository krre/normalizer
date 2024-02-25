#pragma once
#include "Settings.h"

class FileSettings : public Settings {
public:
    FileSettings();

    void setMainWindow(const MainWindow& mainWindow) override;
    MainWindow mainWindow() const override;

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
};
