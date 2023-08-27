#pragma once
#include "StandardDialog.h"
#include "norm/Project.h"

class QLineEdit;
class QComboBox;
class BrowseLayout;

class NewProject : public StandardDialog {
public:
    NewProject(const QString& directory, QWidget* parent = nullptr);

    QString name() const;
    QString directory() const;
    Norm::Project::Template projectTemplate() const;

private slots:
    void adjustAcceptedButton();

private:
    QLineEdit* m_nameLineEdit = nullptr;
    BrowseLayout* m_directoryBrowseLayout = nullptr;
    QComboBox* m_templateComboBox = nullptr;
};
