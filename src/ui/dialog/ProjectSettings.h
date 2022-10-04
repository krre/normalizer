#pragma once
#include "StandardDialog.h"

class FormatComboBox;

namespace Dialog {

class ProjectSettings : public StandardDialog {
public:
    ProjectSettings();
    ~ProjectSettings();

private slots:
    void accept() override;

private:
    FormatComboBox* formatComboBox = nullptr;
};

}
