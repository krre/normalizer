#pragma once
#include "ui/dialog/StandardDialog.h"
#include "core/async/Task.h"

class QLineEdit;

class RegisterAccountDialog : public StandardDialog {
public:
    RegisterAccountDialog();

public slots:
    void accept() override;

private:
    QLineEdit* m_urlLineEdit = nullptr;
    QLineEdit* m_signLineEdit = nullptr;
    QLineEdit* m_nameLineEdit = nullptr;
    QLineEdit* m_emailLineEdit = nullptr;
    QLineEdit* m_passwordLineEdit = nullptr;
    QLineEdit* m_confirmPasswordLineEdit = nullptr;

private slots:
    void enableOkButton();
    Async::Task<void> getToken();
};
