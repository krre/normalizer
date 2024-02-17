#pragma once
#include "ui/dialog/StandardDialog.h"

class Settings;
class BrowseLayout;

class QFormLayout;
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
    void switchLocation();

private:
    Settings* m_settings = nullptr;

    QFormLayout* m_formLayout = nullptr;
    QLineEdit* m_nameLineEdit = nullptr;
    QLineEdit* m_descriptionLineEdit = nullptr;
    QLineEdit* m_hostLineEdit = nullptr;
    QComboBox* m_targetComboBox = nullptr;
    QComboBox* m_locationComboBox = nullptr;
    BrowseLayout* m_directoryBrowseLayout = nullptr;
};
