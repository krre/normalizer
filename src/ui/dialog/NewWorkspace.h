#pragma once
#include "StandardDialog.h"

class QLineEdit;

class NewWorkspace : public StandardDialog {
    Q_OBJECT
public:
    NewWorkspace();

    QString name() const;

public slots:
    void accept() override;

private slots:
    void setOkButtonState();

private:
    QLineEdit* m_nameLineEdit = nullptr;
};
