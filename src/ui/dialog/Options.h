#pragma once
#include "StandardDialog.h"

class QLineEdit;
class QCheckBox;

class Options : public StandardDialog {
public:
    explicit Options(QWidget* parent = nullptr);

private slots:
    void accept() override;

    void onWorkspaceClicked();

private:
    void readSettings();
    void writeSettings();

    QLineEdit* workspaceLineEdit = nullptr;
    QCheckBox* sessionCheckBox = nullptr;
};
