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
    QGroupBox* createNormHostGroupBox();

    Settings* m_settings = nullptr;
    QLineEdit* m_urlLineEdit = nullptr;
};
