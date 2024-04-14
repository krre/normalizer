#pragma once
#include "ui/dialog/StandardDialog.h"

class Settings;

class QLineEdit;
class QComboBox;

class NewProjectDialog : public StandardDialog {
    Q_OBJECT
public:
    NewProjectDialog(Settings* settings);

public slots:
    void accept() override;

private slots:
    void enableOkButton();

private:
    Settings* m_settings = nullptr;

    QLineEdit* m_nameLineEdit = nullptr;
    QComboBox* m_targetComboBox = nullptr;
};
