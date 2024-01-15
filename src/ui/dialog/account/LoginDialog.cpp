#include "LoginDialog.h"
#include "external/network/controller/account/Account.h"
#include "external/network/RestApi.h"
#include <QtWidgets>

LoginDialog::LoginDialog(Controller::Account* account) : m_account(account) {
    setWindowTitle(tr("Log In"));

    m_emailLineEdit = new QLineEdit;
    connect(m_emailLineEdit, &QLineEdit::textChanged, this, &LoginDialog::enableOkButton);

    m_passwordLineEdit = new QLineEdit;
    m_passwordLineEdit->setEchoMode(QLineEdit::Password);
    connect(m_passwordLineEdit, &QLineEdit::textChanged, this, &LoginDialog::enableOkButton);

    auto formLayout = new QFormLayout;
    formLayout->addRow(tr("Email:"), m_emailLineEdit);
    formLayout->addRow(tr("Password:"), m_passwordLineEdit);

    setContentLayout(formLayout);
    resizeToWidth(300);
    m_emailLineEdit->setFocus();
    enableOkButton();
}

QString LoginDialog::token() const {
    return m_token;
}

void LoginDialog::accept() {
    getToken();
}

void LoginDialog::enableOkButton() {
    buttonBox()->button(QDialogButtonBox::Ok)->setEnabled(!m_emailLineEdit->text().isEmpty() &&
                                                          !m_passwordLineEdit->text().isEmpty());
}

Async::Task<void> LoginDialog::getToken() {
    Controller::Account::LoginParams account;
    account.email = m_emailLineEdit->text();
    account.password = m_passwordLineEdit->text();

    try {
        auto response = co_await m_account->login(account);
        m_token = response.token;
        StandardDialog::accept();
    } catch (RestException& e) {
        QString message = e.message();

        if (e.status() == RestStatus::NotFound) {
            message = tr("Email not found");
        } else if (e.status() == RestStatus::Unauthorized) {
            message = tr("Wrong password");
        }

        errorMessage(message);
    }
}
