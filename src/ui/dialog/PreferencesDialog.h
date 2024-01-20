#pragma once
#include "StandardDialog.h"

class QLineEdit;
class Settings;

class PreferencesDialog : public StandardDialog {
public:
    PreferencesDialog(Settings* settings, QWidget* parent = nullptr);

public slots:
    void accept() override;

private:
    Settings* m_settings = nullptr;

    QLineEdit* m_apilLineEdit = nullptr;
};
