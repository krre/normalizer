#pragma once
#include "ui/dialog/StandardDialog.h"

class Settings;

class QLineEdit;
class QComboBox;

class BrowseLayout;

class NewProjectDialog : public StandardDialog {
    Q_OBJECT
public:
    NewProjectDialog(Settings* settings);
    ~NewProjectDialog();

private slots:
    void enableOkButton();

private:
    Settings* m_settings = nullptr;

    QLineEdit* m_nameLineEdit = nullptr;
    QLineEdit* m_descriptionLineEdit = nullptr;
    QComboBox* m_targetComboBox = nullptr;
    QComboBox* m_locationComboBox = nullptr;
    BrowseLayout* m_directoryBrowseLayout = nullptr;
};
