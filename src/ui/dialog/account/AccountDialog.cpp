#include "AccountDialog.h"
#include "ChangePasswordDialog.h"
#include "network/controller/account/Account.h"
#include "core/Constants.h"
#include <QtWidgets>

AccountDialog::AccountDialog(Controller::Account* account) : m_account(account) {
    setWindowTitle(tr("Account"));

    m_loginLineEdit = new QLineEdit;
    m_loginLineEdit->setReadOnly(true);

    m_emailLineEdit = new QLineEdit;
    m_emailLineEdit->setReadOnly(true);

    m_fullNameLineEdit = new QLineEdit;

    auto formLayout = new QFormLayout;
    formLayout->addRow(tr("Login:"), m_loginLineEdit);
    formLayout->addRow(tr("Email:"), m_emailLineEdit);
    formLayout->addRow(tr("Full name:"), m_fullNameLineEdit);

    auto changePasswordButton = new QPushButton(tr("Change Password..."));
    connect(changePasswordButton, &QPushButton::clicked, this, &AccountDialog::openChangePasswordDialog);

    auto deleteButton = new QPushButton(tr("Delete..."));
    connect(deleteButton, &QPushButton::clicked, this, &AccountDialog::deleteAccount);

    auto buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(changePasswordButton);
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addStretch(1);

    auto dialogLayout = new QVBoxLayout;
    dialogLayout->addLayout(formLayout);
    dialogLayout->addLayout(buttonLayout);

    setContentLayout(dialogLayout);
    resizeToWidth(500);
    m_fullNameLineEdit->setFocus();
    getAccount();
}

void AccountDialog::accept() {
    updateAccount();
}

void AccountDialog::openChangePasswordDialog() {
    ChangePasswordDialog changePasswordDialog(m_account);

    if (changePasswordDialog.exec() == QDialog::Accepted) {
        QMessageBox::information(this, Const::App::Name, tr("Password successfully changed!"));
    }
}

Async::Task<void> AccountDialog::deleteAccount() {
    if (QMessageBox::warning(this, Const::App::Name,
                             tr("Account will be deleted along with all your projects without the possibility of recovery!"),
                             QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Cancel) != QMessageBox::Ok) {
        co_return;
    }

    co_await m_account->remove();
    m_result = Result::Deleted;
    StandardDialog::accept();
}

Async::Task<void> AccountDialog::getAccount() {
    Controller::Account::GetAccount account = co_await m_account->getOne();
    m_loginLineEdit->setText(account.login);
    m_emailLineEdit->setText(account.email);
    m_fullNameLineEdit->setText(account.fullName);
}

Async::Task<void> AccountDialog::updateAccount() {
    Controller::Account::UpdateAccount account;
    account.fullName = m_fullNameLineEdit->text();

    co_await m_account->update(account);
    StandardDialog::accept();
}
