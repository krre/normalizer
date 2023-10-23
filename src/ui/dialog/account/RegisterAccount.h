#pragma once
#include "ui/dialog/StandardDialog.h"

class QLineEdit;

class RegisterAccount : public StandardDialog {
public:
    RegisterAccount();

private:
    QLineEdit* m_urlLineEdit = nullptr;
    QLineEdit* m_signLineEdit = nullptr;
    QLineEdit* m_nameLineEdit = nullptr;
    QLineEdit* m_emailLineEdit = nullptr;
    QLineEdit* m_passwordLineEdit = nullptr;

public slots:
    void accept() override;

private slots:
    void enableOkButton();
};
