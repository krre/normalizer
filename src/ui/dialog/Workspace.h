#pragma once
#include "StandardDialog.h"

class BrowseLineEdit;

class Workspace : public StandardDialog {
public:
    explicit Workspace(QWidget* parent = nullptr);

protected slots:
    void accept() override;

private slots:
    void adjustAcceptedButton(const QString& text);

private:
    BrowseLineEdit* workspaceBrowseLineEdit = nullptr;
};
