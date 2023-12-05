#pragma once
#include "ui/dialog/StandardDialog.h"
#include "core/async/Task.h"

namespace Controller {
    class AbstractAccount;
}

class QLineEdit;

class LoginDialog : public StandardDialog {
public:
    LoginDialog(Controller::AbstractAccount* account);
    QString token() const;

public slots:
    void accept() override;

private:
    QLineEdit* m_emailLineEdit = nullptr;
    QLineEdit* m_passwordLineEdit = nullptr;

private slots:
    void enableOkButton();
    Async::Task<void> getToken();

private:
    Controller::AbstractAccount* m_account = nullptr;
    QString m_token;
};
