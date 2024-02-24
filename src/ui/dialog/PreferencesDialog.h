#pragma once
#include "StandardDialog.h"

class Settings;
class BrowseLayout;

class QGroupBox;
class QLineEdit;

class PreferencesDialog : public StandardDialog {
public:
    PreferencesDialog(Settings* settings, QWidget* parent = nullptr);

public slots:
    void accept() override;

private:
    QGroupBox* createProjectLocationGroupBox();

    Settings* m_settings = nullptr;

    BrowseLayout* m_workspaceBrowseLayout = nullptr;
    QLineEdit* m_hostLineEdit = nullptr;
};
