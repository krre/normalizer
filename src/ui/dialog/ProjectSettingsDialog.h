#pragma once
#include "StandardDialog.h"

class ProjectSettings;
class FormatComboBox;

class ProjectSettingsDialog : public StandardDialog {
public:
    ProjectSettingsDialog(const QString& projectPath);
    ~ProjectSettingsDialog();

private slots:
    void accept() override;

private:
    QScopedPointer<ProjectSettings> settings;
    FormatComboBox* formatComboBox = nullptr;
};
