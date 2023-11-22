#include "ChangePasswordDialog.h"
#include "ui/dialog/DialogMessages.h"
#include <QtWidgets>

ChangePasswordDialog::ChangePasswordDialog(NetworkManager* networkManager) : m_networkManager(networkManager) {
    setWindowTitle(tr("Change Password"));

    m_oldPasswordLineEdit = new QLineEdit;
    m_oldPasswordLineEdit->setEchoMode(QLineEdit::Password);
    connect(m_oldPasswordLineEdit, &QLineEdit::textChanged, this, &ChangePasswordDialog::enableOkButton);

    m_newPasswordLineEdit = new QLineEdit;
    m_newPasswordLineEdit->setEchoMode(QLineEdit::Password);
    connect(m_newPasswordLineEdit, &QLineEdit::textChanged, this, &ChangePasswordDialog::enableOkButton);

    m_confirmPasswordLineEdit = new QLineEdit;
    m_confirmPasswordLineEdit->setEchoMode(QLineEdit::Password);
    connect(m_confirmPasswordLineEdit, &QLineEdit::textChanged, this, &ChangePasswordDialog::enableOkButton);

    auto formLayout = new QFormLayout;
    formLayout->addRow(tr("Old password:"), m_oldPasswordLineEdit);
    formLayout->addRow(tr("New password:"), m_newPasswordLineEdit);
    formLayout->addRow(tr("Confirm password:"), m_confirmPasswordLineEdit);

    setContentLayout(formLayout);
    resizeToWidth(400);
    m_oldPasswordLineEdit->setFocus();
    enableOkButton();
}

void ChangePasswordDialog::accept() {
    if (m_newPasswordLineEdit->text() != m_confirmPasswordLineEdit->text()) {
        errorMessage(DialogMessages::PasswordMismatch);
        return;
    }

    StandardDialog::accept();
}

void ChangePasswordDialog::enableOkButton() {
    buttonBox()->button(QDialogButtonBox::Ok)->setEnabled(!m_oldPasswordLineEdit->text().isEmpty() &&
                                                          !m_newPasswordLineEdit->text().isEmpty() &&
                                                          !m_confirmPasswordLineEdit->text().isEmpty());
}
