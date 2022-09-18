#pragma once
#include "StandardDialog.h"

class ProjectSettings;
class FormatComboBox;

class ProjectSettingsDialog : public StandardDialog {
public:
    ProjectSettingsDialog();
    ~ProjectSettingsDialog();

private slots:
    void accept() override;

private:
    FormatComboBox* formatComboBox = nullptr;
};
