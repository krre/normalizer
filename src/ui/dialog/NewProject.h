#pragma once
#include "StandardDialog.h"
#include <NormCore/Project.h>
#include <NormCore/Global.h>

class QLineEdit;
class QComboBox;

class NewProject : public StandardDialog {
    Q_OBJECT
public:
    explicit NewProject();
    QString path() const;
    NormCore::Project::Template projectTemplate() const;

private slots:
    void accept() override;
    void onBrowseButtonClicked();
    void adjustAcceptedButton();

private:
    QLineEdit* nameLineEdit = nullptr;
    QLineEdit* directoryLineEdit = nullptr;
    QComboBox* templateComboBox = nullptr;
};
