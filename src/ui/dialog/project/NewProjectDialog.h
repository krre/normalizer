#pragma once
#include "ui/dialog/StandardDialog.h"

class Process;
class Settings;
class BrowseLayout;

class QLineEdit;
class QComboBox;

class NewProjectDialog : public StandardDialog {
    Q_OBJECT
public:
    NewProjectDialog(Process* process, Settings* settings);

public slots:
    void accept() override;

private slots:
    void enableOkButton();

private:
    Process* m_process = nullptr;
    Settings* m_settings = nullptr;

    QLineEdit* m_nameLineEdit = nullptr;
    QComboBox* m_targetComboBox = nullptr;
    BrowseLayout* m_workspaceBrowseLayout = nullptr;
};
