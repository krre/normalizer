#pragma once
#include "ui/dialog/StandardDialog.h"
#include "core/async/Task.h"

namespace Controller {
    class AbstractAccount;
}

class QLineEdit;

class RegisterAccountDialog : public StandardDialog {
public:
    RegisterAccountDialog(Controller::AbstractAccount* account);
    QString token() const;

public slots:
    void accept() override;

private:
    QLineEdit* m_loginLineEdit = nullptr;
    QLineEdit* m_fullNameLineEdit = nullptr;
    QLineEdit* m_emailLineEdit = nullptr;
    QLineEdit* m_passwordLineEdit = nullptr;
    QLineEdit* m_confirmPasswordLineEdit = nullptr;

private slots:
    void enableOkButton();
    Async::Task<void> getToken();

private:
    Controller::AbstractAccount* m_account = nullptr;
    QString m_token;
};
