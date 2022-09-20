#pragma once
#include "StandardDialog.h"
#include <NormCommon/Project.h>

class BrowseLineEdit;
class FormatComboBox;
class QComboBox;
class QLineEdit;

class NewProject : public StandardDialog {
    Q_OBJECT
public:
    explicit NewProject();
    QString path() const;

private slots:
    void accept() override;
    void adjustAcceptedButton();

private:
    NormCommon::Project::Target target() const;

    QLineEdit* nameLineEdit = nullptr;
    BrowseLineEdit* directoryBrowseLineEdit = nullptr;
    QComboBox* targetComboBox = nullptr;
};
