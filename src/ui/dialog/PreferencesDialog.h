#pragma once
#include "StandardDialog.h"

class Settings;
class BrowseLayout;

class QLineEdit;

class PreferencesDialog : public StandardDialog {
public:
    PreferencesDialog(Settings* settings, QWidget* parent = nullptr);

public slots:
    void accept() override;

private:
    Settings* m_settings = nullptr;

    BrowseLayout* m_directoryBrowseLayout = nullptr;
    QLineEdit* m_hostLineEdit = nullptr;
};
