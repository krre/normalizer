#pragma once
#include "ui/dialog/StandardDialog.h"
#include "core/async/Task.h"

namespace Controller {
    class Account;
}

class QLineEdit;

class ChangePasswordDialog : public StandardDialog {
public:
    ChangePasswordDialog(Controller::Account* account);

public slots:
    void accept() override;

private slots:
    void enableOkButton();

private:
    Async::Task<void> changePassword();

    Controller::Account* m_account = nullptr;

    QLineEdit* m_oldPasswordLineEdit = nullptr;
    QLineEdit* m_newPasswordLineEdit = nullptr;
    QLineEdit* m_confirmPasswordLineEdit = nullptr;
};
