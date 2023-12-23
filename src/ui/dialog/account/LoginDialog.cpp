#include "LoginDialog.h"
#include "core/Constants.h"
#include "network/controller/account/Account.h"
#include "network/http/HttpNetwork.h"
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
    Controller::Account::LoginAccount account;
    account.email = m_emailLineEdit->text();
    account.password = m_passwordLineEdit->text();

    try {
        m_token = co_await m_account->login(account);
        StandardDialog::accept();
    } catch (HttpException& e) {
        QString message = e.message();

        if (e.status() == Const::HttpStatus::NotFound) {
            message = tr("Email not found");
        } else if (e.status() == Const::HttpStatus::Unauthorized) {
            message = tr("Wrong password");
        }

        errorMessage(message);
    }
}
