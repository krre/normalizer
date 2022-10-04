#pragma once
#include "StandardDialog.h"
#include "project/Project.h"

class BrowseLineEdit;
class FormatComboBox;
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
    Project::Target target() const;

    QLineEdit* nameLineEdit = nullptr;
    BrowseLineEdit* directoryBrowseLineEdit = nullptr;
    QComboBox* targetComboBox = nullptr;
    FormatComboBox* formatComboBox = nullptr;
};

}
