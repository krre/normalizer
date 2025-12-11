#pragma once
#include "StandardDialog.h"

class Settings;
class QLineEdit;
class QCheckBox;
class QSpinBox;

class Preferences : public StandardDialog {
    Q_OBJECT
public:
    Preferences(Settings* settings);

public slots:
    void accept() override;

private:
    void readSettings();
    void writeSettings();

    Settings* m_settings = nullptr;
    QLineEdit* m_workDirLineEdit = nullptr;
    QLineEdit* m_hostLineEdit = nullptr;
    QSpinBox* m_portLineEdit = nullptr;
    QCheckBox* m_loadLastProjectCheckBox = nullptr;
    QCheckBox* m_vulkanCheckBox = nullptr;
};
