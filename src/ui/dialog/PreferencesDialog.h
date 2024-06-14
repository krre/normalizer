#pragma once
#include "StandardDialog.h"

class Settings;

class QGroupBox;
class QLineEdit;
class QComboBox;

class PreferencesDialog : public StandardDialog {
    Q_OBJECT
public:
    PreferencesDialog(const QStringList& adapters, Settings* settings, QWidget* parent = nullptr);

public slots:
    void accept() override;

private:
    QGroupBox* createDevelopmentServerGroupBox();
    QGroupBox* createGraphicsGroupBox(const QStringList& adapters);

    Settings* m_settings = nullptr;
    QLineEdit* m_urlLineEdit = nullptr;
    QComboBox* m_adapterComboBox = nullptr;
};
