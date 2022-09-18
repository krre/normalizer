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
    NormCommon::Project::Template projectTemplate() const;
    NormCommon::Project::Format format() const;

    QLineEdit* nameLineEdit = nullptr;
    BrowseLineEdit* directoryBrowseLineEdit = nullptr;
    QComboBox* templateComboBox = nullptr;
    FormatComboBox* formatComboBox = nullptr;
};
