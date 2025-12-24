#pragma once
#include "project/Project.h"
#include "StandardDialog.h"

class BrowseLayout;

class QLineEdit;
class QComboBox;

class NewProject : public StandardDialog {
    Q_OBJECT
public:
    NewProject();

    QString name() const;
    QString directory() const;
    Project::Target target() const;

public slots:
    void accept() override;

private slots:
    void setOkButtonState();

private:
    QLineEdit* m_nameLineEdit = nullptr;
    BrowseLayout* m_directoryBrowseLayout = nullptr;
    QComboBox* m_targetComboBox = nullptr;
};
