#pragma once
#include "StandardDialog.h"
#include "project/ProjectManager.h"

class BrowseLineEdit;
class QComboBox;
class QLineEdit;

namespace Dialog {

class NewProject : public StandardDialog {
public:
    explicit NewProject();
    QString path() const;

private slots:
    void accept() override;
    void adjustAcceptedButton();

private:
    ProjectManager::Target target() const;

    QLineEdit* nameLineEdit = nullptr;
    BrowseLineEdit* directoryBrowseLineEdit = nullptr;
    QComboBox* targetComboBox = nullptr;
};

}
