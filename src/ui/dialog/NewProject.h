#pragma once
#include "StandardDialog.h"
#include <NormCommon/Project.h>
#include <NormCommon/Global.h>

class QLineEdit;
class QComboBox;

class NewProject : public StandardDialog {
    Q_OBJECT
public:
    explicit NewProject();
    QString path() const;
    NormCommon::Project::Template projectTemplate() const;

private slots:
    void accept() override;
    void onBrowseButtonClicked();
    void adjustAcceptedButton();

private:
    QLineEdit* nameLineEdit = nullptr;
    QLineEdit* directoryLineEdit = nullptr;
    QComboBox* templateComboBox = nullptr;
};
