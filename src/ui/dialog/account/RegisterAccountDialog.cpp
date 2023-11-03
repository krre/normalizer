#include "RegisterAccountDialog.h"
#include "core/Settings.h"
#include "manager/network/NetworkManager.h"
#include <QtWidgets>

RegisterAccountDialog::RegisterAccountDialog() {
    setWindowTitle(tr("Register Account"));

    m_urlLineEdit = new QLineEdit("http://localhost:3000");
    connect(m_urlLineEdit, &QLineEdit::textChanged, this, &RegisterAccountDialog::enableOkButton);

    m_signLineEdit = new QLineEdit;
    connect(m_signLineEdit, &QLineEdit::textChanged, this, &RegisterAccountDialog::enableOkButton);

    m_nameLineEdit = new QLineEdit;
    connect(m_nameLineEdit, &QLineEdit::textChanged, this, &RegisterAccountDialog::enableOkButton);

    m_emailLineEdit = new QLineEdit;
    connect(m_emailLineEdit, &QLineEdit::textChanged, this, &RegisterAccountDialog::enableOkButton);

    m_passwordLineEdit = new QLineEdit;
    m_passwordLineEdit->setEchoMode(QLineEdit::Password);
    connect(m_passwordLineEdit, &QLineEdit::textChanged, this, &RegisterAccountDialog::enableOkButton);

    m_confirmPasswordLineEdit = new QLineEdit;
    m_confirmPasswordLineEdit->setEchoMode(QLineEdit::Password);
    connect(m_confirmPasswordLineEdit, &QLineEdit::textChanged, this, &RegisterAccountDialog::enableOkButton);

    auto formLayout = new QFormLayout;
    formLayout->addRow(tr("URL:"), m_urlLineEdit);
    formLayout->addRow(tr("Sign:"), m_signLineEdit);
    formLayout->addRow(tr("Full name:"), m_nameLineEdit);
    formLayout->addRow(tr("Email:"), m_emailLineEdit);
    formLayout->addRow(tr("Password:"), m_passwordLineEdit);
    formLayout->addRow(tr("Confirm password:"), m_confirmPasswordLineEdit);

    setContentLayout(formLayout);
    resizeToWidth(500);
    m_signLineEdit->setFocus();
    enableOkButton();
}

void RegisterAccountDialog::accept() {
    if (m_passwordLineEdit->text() != m_confirmPasswordLineEdit->text()) {
        QMessageBox::critical(this, tr("Confirm Password Error"), tr("Password mismatch!"));
        return;
    }

    getToken();
}

void RegisterAccountDialog::enableOkButton() {
    buttonBox()->button(QDialogButtonBox::Ok)->setEnabled(!m_urlLineEdit->text().isEmpty() &&
                                                          !m_signLineEdit->text().isEmpty() &&
                                                          !m_nameLineEdit->text().isEmpty() &&
                                                          !m_emailLineEdit->text().isEmpty() &&
                                                          !m_passwordLineEdit->text().isEmpty() &&
                                                          !m_confirmPasswordLineEdit->text().isEmpty());
}

Async::Task<void> RegisterAccountDialog::getToken() {
    NetworkManager::User user;
    user.sign = m_signLineEdit->text();
    user.name = m_nameLineEdit->text();
    user.email = m_emailLineEdit->text();
    user.password = m_passwordLineEdit->text();

    try {
        NetworkManager networkManager;
        QString token = co_await networkManager.registerUser(m_urlLineEdit->text(), user);
        Settings::setValue<Account::Token>(token);
        StandardDialog::accept();
    } catch (NetworkException& e) {
        QString message = e.status() == Const::HttpStatus::Conflict ? tr("Account already exists") : e.message();
        QMessageBox::critical(this, tr("Register error"), message);
    } catch (std::exception& e) {
        QMessageBox::critical(this, tr("Register error"), e.what());
    }
}
