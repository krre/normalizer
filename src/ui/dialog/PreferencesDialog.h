#pragma once
#include "StandardDialog.h"

class Settings;
class BrowseLayout;

class QGroupBox;
class QLineEdit;
class QComboBox;

class PreferencesDialog : public StandardDialog {
public:
    PreferencesDialog(Settings* settings, QWidget* parent = nullptr);

public slots:
    void accept() override;

private:
    QGroupBox* createDevelopmentServerGroupBox();
    QGroupBox* createGraphicsGroupBox();

    Settings* m_settings = nullptr;
    QLineEdit* m_urlLineEdit = nullptr;
    QComboBox* m_adapterComboBox = nullptr;
};
