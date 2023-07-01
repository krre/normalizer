#pragma once
#include "StandardDialog.h"
#include "project/Project.h"

class QLineEdit;
class QComboBox;
class BrowseLayout;

class NewProject : public StandardDialog {
public:
    NewProject(QWidget* parent = nullptr);

    QString name() const;
    QString directory() const;
    Project::Template projectTemplate() const;

private slots:
    void adjustAcceptedButton();

private:
    QLineEdit* m_nameLineEdit = nullptr;
    BrowseLayout* m_directoryBrowseLayout = nullptr;
    QComboBox* m_templateComboBox = nullptr;
};
