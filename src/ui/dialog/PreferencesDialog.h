#pragma once
#include "StandardDialog.h"
#include "manager/settings/SettingsStorage.h"

class QLineEdit;

class PreferencesDialog : public StandardDialog {
public:
    PreferencesDialog(SettingsStorage* settingsStorage, QWidget* parent = nullptr);

public slots:
    void accept() override;

private:
    SettingsStorage* m_settingsStorage = nullptr;

    QLineEdit* m_hostLineEdit = nullptr;
    QLineEdit* m_portLineEdit = nullptr;
};
