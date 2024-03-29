#pragma once
#include "ui/dialog/StandardDialog.h"
#include "core/async/Task.h"

namespace Controller {
    class Account;
}

class QLineEdit;

class AccountDialog : public StandardDialog {
public:
    enum class Result {
        None,
        Deleted
    };

    AccountDialog(Controller::Account* account);
    Result result() const { return m_result; }

public slots:
    void accept() override;

private slots:
    void openChangePasswordDialog();

    Async::Task<void> deleteAccount();
    Async::Task<void> getAccount();
    Async::Task<void> updateAccount();

private:
    Controller::Account* m_account = nullptr;

    QLineEdit* m_loginLineEdit = nullptr;
    QLineEdit* m_fullNameLineEdit = nullptr;
    QLineEdit* m_emailLineEdit = nullptr;

    Result m_result = Result::None;
};
