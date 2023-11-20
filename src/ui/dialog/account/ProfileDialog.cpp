#include "ProfileDialog.h"
#include "ui/dialog/DialogMessages.h"
#include "manager/network/HttpNetworkManager.h"
#include <QtWidgets>

ProfileDialog::ProfileDialog(NetworkManager* networkManager) : m_networkManager(networkManager) {
    setWindowTitle(tr("Profile"));

    m_loginLineEdit = new QLineEdit;
    m_loginLineEdit->setReadOnly(true);

    m_emailLineEdit = new QLineEdit;
    m_emailLineEdit->setReadOnly(true);

    m_fullNameLineEdit = new QLineEdit;

    m_passwordLineEdit = new QLineEdit;
    m_passwordLineEdit->setEchoMode(QLineEdit::Password);

    m_confirmPasswordLineEdit = new QLineEdit;
    m_confirmPasswordLineEdit->setEchoMode(QLineEdit::Password);

    auto deleteButton = new QPushButton(tr("Delete Account..."));
    connect(deleteButton, &QPushButton::clicked, this, &ProfileDialog::deleteAccount);

    auto formLayout = new QFormLayout;
    formLayout->addRow(tr("Login:"), m_loginLineEdit);
    formLayout->addRow(tr("Email:"), m_emailLineEdit);
    formLayout->addRow(tr("Full name:"), m_fullNameLineEdit);
    formLayout->addRow(tr("Password:"), m_passwordLineEdit);
    formLayout->addRow(tr("Confirm password:"), m_confirmPasswordLineEdit);
    formLayout->addRow("", deleteButton);

    formLayout->itemAt(formLayout->indexOf(deleteButton))->setAlignment(Qt::AlignLeft);

    setContentLayout(formLayout);
    resizeToWidth(500);
    m_fullNameLineEdit->setFocus();
    getProfile();
}

void ProfileDialog::accept() {
    if (m_passwordLineEdit->text() != m_confirmPasswordLineEdit->text()) {
        errorMessage(DialogMessages::PasswordMismatch);
        return;
    }

    updateProfile();
}

Async::Task<void> ProfileDialog::deleteAccount() {
    if (QMessageBox::warning(this,
                             tr("Confirm Deleting Account"),
                             tr("Account will be deleted along with all your projects without the possibility of recovery!"),
                             QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Cancel) != QMessageBox::Ok) {
        co_return;
    }

    try {
        co_await m_networkManager->deleteUser();
        close();
    } catch (NetworkException& e) {
        errorMessage(e.message());
    } catch (std::exception& e) {
        errorMessage(e.what());
    }
}

Async::Task<void> ProfileDialog::getProfile() {
    try {
        HttpNetworkManager::User user = co_await m_networkManager->getUser();
        m_loginLineEdit->setText(user.login);
        m_emailLineEdit->setText(user.email);
        m_fullNameLineEdit->setText(user.fullName);
    } catch (NetworkException& e) {
        errorMessage(e.message());
    } catch (std::exception& e) {
        errorMessage(e.what());
    }
}

Async::Task<void> ProfileDialog::updateProfile() {
    StandardDialog::accept();
    co_return;
}
