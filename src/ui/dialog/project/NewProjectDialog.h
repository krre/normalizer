#pragma once
#include "ui/dialog/StandardDialog.h"

class Settings;
class BrowseLayout;

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
    QLineEdit* m_descriptionLineEdit = nullptr;
    QComboBox* m_targetComboBox = nullptr;
    BrowseLayout* m_workspaceBrowseLayout = nullptr;
};
