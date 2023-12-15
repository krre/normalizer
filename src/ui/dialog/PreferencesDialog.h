#pragma once
#include "StandardDialog.h"
#include "manager/settings/Settings.h"

class QLineEdit;

class PreferencesDialog : public StandardDialog {
public:
    PreferencesDialog(Settings* settings, QWidget* parent = nullptr);

public slots:
    void accept() override;

private:
    Settings* m_settings = nullptr;

    QLineEdit* m_urlLineEdit = nullptr;
};
