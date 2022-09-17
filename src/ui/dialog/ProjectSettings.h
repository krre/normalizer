#pragma once
#include "StandardDialog.h"

class ProjectSettings : public StandardDialog {
public:
    ProjectSettings();

private slots:
    void accept() override;
};
