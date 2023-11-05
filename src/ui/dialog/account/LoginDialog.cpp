#include "LoginDialog.h"
#include "manager/network/HttpNetworkManager.h"
#include "core/Constants.h"
#include <QtWidgets>

LoginDialog::LoginDialog(NetworkManager* networkManager) : m_networkManager(networkManager) {
    setWindowTitle(tr("Login"));

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
    HttpNetworkManager::User user;
    user.email = m_emailLineEdit->text();
    user.password = m_passwordLineEdit->text();

    try {
        m_token = co_await m_networkManager->login(user);
        StandardDialog::accept();
    } catch (NetworkException& e) {
        QString message = e.message();

        if (e.status() == Const::HttpStatus::NotFound) {
            message = tr("Email not found");
        } else if (e.status() == Const::HttpStatus::Unauthorized) {
            message = tr("Wrong password");
        }

        QMessageBox::critical(this, tr("Login error"), message);
    } catch (std::exception& e) {
        QMessageBox::critical(this, tr("Login error"), e.what());
    }
}
