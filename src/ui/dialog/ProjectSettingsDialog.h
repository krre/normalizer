#pragma once
#include "StandardDialog.h"

class ProjectSettings;
class QComboBox;

class ProjectSettingsDialog : public StandardDialog {
public:
    ProjectSettingsDialog();
    ~ProjectSettingsDialog();

private slots:
    void accept() override;

private:
    QComboBox* formatComboBox = nullptr;
};
