#pragma once
#include "StandardDialog.h"

class QComboBox;

namespace Dialog {

class ProjectSettings : public StandardDialog {
public:
    ProjectSettings();
    ~ProjectSettings();

private slots:
    void accept() override;

private:
    QComboBox* formatComboBox = nullptr;
};

}
