#pragma once
#include "StandardDialog.h"

class FormatComboBox;

class ProjectSettings : public StandardDialog {
public:
    ProjectSettings();

private slots:
    void accept() override;

private:
    FormatComboBox* formatComboBox = nullptr;
};
