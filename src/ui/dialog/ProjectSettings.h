#pragma once
#include "StandardDialog.h"

namespace Dialog {

class ProjectSettings : public StandardDialog {
public:
    ProjectSettings();
    ~ProjectSettings();

private slots:
    void accept() override;
};

}
