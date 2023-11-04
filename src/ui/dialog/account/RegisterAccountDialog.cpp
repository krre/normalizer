#include "RegisterAccountDialog.h"
#include "manager/network/NetworkManager.h"
#include "core/Constants.h"
#include <QtWidgets>

RegisterAccountDialog::RegisterAccountDialog(AbstractNetworkManager* networkManager) : m_networkManager(networkManager) {
    setWindowTitle(tr("Register Account"));

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

QString RegisterAccountDialog::token() const {
    return m_token;
}

void RegisterAccountDialog::accept() {
    if (m_passwordLineEdit->text() != m_confirmPasswordLineEdit->text()) {
        QMessageBox::critical(this, tr("Confirm Password Error"), tr("Password mismatch!"));
        return;
    }

    getToken();
}

void RegisterAccountDialog::enableOkButton() {
    buttonBox()->button(QDialogButtonBox::Ok)->setEnabled(!m_signLineEdit->text().isEmpty() &&
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
        m_token = co_await m_networkManager->registerUser(user);
        StandardDialog::accept();
    } catch (NetworkException& e) {
        QString message = e.status() == Const::HttpStatus::Conflict ? tr("Account already exists") : e.message();
        QMessageBox::critical(this, tr("Register error"), message);
    } catch (std::exception& e) {
        QMessageBox::critical(this, tr("Register error"), e.what());
    }
}
