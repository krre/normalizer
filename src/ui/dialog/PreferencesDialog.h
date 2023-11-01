#pragma once
#include "StandardDialog.h"
#include "manager/settings/AbstractSettingsManager.h"

class QLineEdit;

class PreferencesDialog : public StandardDialog {
    friend class TestPreferences;
public:
    PreferencesDialog(AbstractSettingsManager* settingsManager, QWidget* parent = nullptr);

public slots:
    void accept() override;

private:
    AbstractSettingsManager* m_settingsManager = nullptr;

    QLineEdit* m_hostLineEdit = nullptr;
    QLineEdit* m_portLineEdit = nullptr;
};
