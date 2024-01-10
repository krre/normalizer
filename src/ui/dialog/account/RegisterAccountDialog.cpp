#include "RegisterAccountDialog.h"
#include "ui/dialog/DialogMessages.h"
#include "external/network/controller/account/Account.h"
#include "external/network/http/HttpNetwork.h"
#include "external/network/http/HttpStatus.h"
#include <QtWidgets>

RegisterAccountDialog::RegisterAccountDialog(Controller::Account* account) : m_account(account) {
    setWindowTitle(tr("Register Account"));

    m_loginLineEdit = new QLineEdit;
    connect(m_loginLineEdit, &QLineEdit::textChanged, this, &RegisterAccountDialog::enableOkButton);

    m_fullNameLineEdit = new QLineEdit;
    connect(m_fullNameLineEdit, &QLineEdit::textChanged, this, &RegisterAccountDialog::enableOkButton);

    m_emailLineEdit = new QLineEdit;
    connect(m_emailLineEdit, &QLineEdit::textChanged, this, &RegisterAccountDialog::enableOkButton);

    m_passwordLineEdit = new QLineEdit;
    m_passwordLineEdit->setEchoMode(QLineEdit::Password);
    connect(m_passwordLineEdit, &QLineEdit::textChanged, this, &RegisterAccountDialog::enableOkButton);

    m_confirmPasswordLineEdit = new QLineEdit;
    m_confirmPasswordLineEdit->setEchoMode(QLineEdit::Password);
    connect(m_confirmPasswordLineEdit, &QLineEdit::textChanged, this, &RegisterAccountDialog::enableOkButton);

    auto formLayout = new QFormLayout;
    formLayout->addRow(tr("Login:"), m_loginLineEdit);
    formLayout->addRow(tr("Full name:"), m_fullNameLineEdit);
    formLayout->addRow(tr("Email:"), m_emailLineEdit);
    formLayout->addRow(tr("Password:"), m_passwordLineEdit);
    formLayout->addRow(tr("Confirm password:"), m_confirmPasswordLineEdit);

    setContentLayout(formLayout);
    resizeToWidth(500);
    m_loginLineEdit->setFocus();
    enableOkButton();
}

QString RegisterAccountDialog::token() const {
    return m_token;
}

void RegisterAccountDialog::accept() {
    if (m_passwordLineEdit->text() != m_confirmPasswordLineEdit->text()) {
        errorMessage(DialogMessages::PasswordMismatch);
        return;
    }

    getToken();
}

void RegisterAccountDialog::enableOkButton() {
    buttonBox()->button(QDialogButtonBox::Ok)->setEnabled(!m_loginLineEdit->text().isEmpty() &&
                                                          !m_fullNameLineEdit->text().isEmpty() &&
                                                          !m_emailLineEdit->text().isEmpty() &&
                                                          !m_passwordLineEdit->text().isEmpty() &&
                                                          !m_confirmPasswordLineEdit->text().isEmpty());
}

Async::Task<void> RegisterAccountDialog::getToken() {
    Controller::Account::CreateAccount account;
    account.login = m_loginLineEdit->text();
    account.fullName = m_fullNameLineEdit->text();
    account.email = m_emailLineEdit->text();
    account.password = m_passwordLineEdit->text();

    try {
        auto response = co_await m_account->create(account);
        m_token = response.token;
        StandardDialog::accept();
    } catch (HttpException& e) {
        QString message = e.status() == HttpStatus::Conflict ? tr("Account already exists") : e.message();
        errorMessage(message);
    }
}
