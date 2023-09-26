#pragma once
#include "StandardDialog.h"
#include "norm/Project.h"

class QLineEdit;
class QComboBox;
class BrowseLayout;

class NewProject : public StandardDialog {
public:
    NewProject(QWidget* parent = nullptr);

    QString name() const;
    Norm::Project::Template projectTemplate() const;

private slots:
    void adjustAcceptedButton();

private:
    QLineEdit* m_nameLineEdit = nullptr;
    QComboBox* m_templateComboBox = nullptr;
};
