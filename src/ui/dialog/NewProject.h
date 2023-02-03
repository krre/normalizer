#pragma once
#include "StandardDialog.h"
#include "norm/project/Project.h"

class BrowseLineEdit;
class QComboBox;
class QGroupBox;
class QLineEdit;

namespace Dialog {

class NewProject : public StandardDialog {
public:
    explicit NewProject();
    QString path() const;

private slots:
    void accept() override;
    void onProjectNameChanged(const QString& projectName);
    void adjustAcceptedButton();

private:
    QGroupBox* createProjectGroupBox();
    QGroupBox* createTargetGroupBox();

    Norm::Project::Target target() const;

    QGroupBox* targetGroupBox = nullptr;
    QLineEdit* projectNameLineEdit = nullptr;
    QLineEdit* targetNameLineEdit = nullptr;
    BrowseLineEdit* projectDirectoryBrowseLineEdit = nullptr;
    QComboBox* targetTypeComboBox = nullptr;
    QString oldProjectName;
};

}
