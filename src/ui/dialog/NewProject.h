#pragma once
#include "project/Project.h"
#include "StandardDialog.h"

class QLineEdit;
class QComboBox;

class NewProject : public StandardDialog {
    Q_OBJECT
public:
    NewProject();

    QString name() const;
    Project::Target target() const;

public slots:
    void accept() override;

private slots:
    void setOkButtonState();

private:
    QLineEdit* m_nameLineEdit = nullptr;
    QComboBox* m_targetComboBox = nullptr;
};
