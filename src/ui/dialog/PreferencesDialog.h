#pragma once
#include "StandardDialog.h"

class Settings;
class BrowseLayout;

class QGroupBox;
class QRadioButton;
class QLineEdit;

class PreferencesDialog : public StandardDialog {
public:
    PreferencesDialog(Settings* settings, QWidget* parent = nullptr);

public slots:
    void accept() override;

private:
    QGroupBox* createProjectLocationGroupBox();
    QGroupBox* createNormLocationGroupBox();

    Settings* m_settings = nullptr;

    BrowseLayout* m_workspaceBrowseLayout = nullptr;
    BrowseLayout* m_customBrowseLayout = nullptr;

    QLineEdit* m_hostLineEdit = nullptr;
    QLineEdit* m_homeLineEdit = nullptr;

    QRadioButton* m_homeRadioButton = nullptr;
    QRadioButton* m_customRadioButton = nullptr;
};
