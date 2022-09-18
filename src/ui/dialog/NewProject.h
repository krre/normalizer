#pragma once
#include "StandardDialog.h"
#include <NormCommon/Project.h>
#include <NormCommon/Global.h>

class BrowseLineEdit;
class FormatComboBox;
class QComboBox;
class QLineEdit;

class NewProject : public StandardDialog {
    Q_OBJECT
public:
    explicit NewProject();
    QString path() const;
    NormCommon::Project::Template projectTemplate() const;
    NormCommon::Project::Format format() const;

private slots:
    void accept() override;
    void adjustAcceptedButton();

private:
    QLineEdit* nameLineEdit = nullptr;
    BrowseLineEdit* directoryBrowseLineEdit = nullptr;
    QComboBox* templateComboBox = nullptr;
    FormatComboBox* formatComboBox = nullptr;
};
