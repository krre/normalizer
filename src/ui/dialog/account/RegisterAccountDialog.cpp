#include "RegisterAccountDialog.h"
#include "ui/dialog/DialogMessages.h"
#include "network/http/HttpNetworkManager.h"
#include "core/Constants.h"
#include <QtWidgets>

RegisterAccountDialog::RegisterAccountDialog(NetworkManager* networkManager) : m_networkManager(networkManager) {
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
    HttpNetworkManager::User user;
    user.login = m_loginLineEdit->text();
    user.fullName = m_fullNameLineEdit->text();
    user.email = m_emailLineEdit->text();
    user.password = m_passwordLineEdit->text();

    try {
        m_token = co_await m_networkManager->createUser(user);
        StandardDialog::accept();
    } catch (NetworkException& e) {
        QString message = e.status() == Const::HttpStatus::Conflict ? tr("Account already exists") : e.message();
        errorMessage(message);
    } catch (std::exception& e) {
        errorMessage(e.what());
    }
}
