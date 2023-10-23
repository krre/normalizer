#include "RegisterAccount.h"
#include <QtWidgets>

RegisterAccount::RegisterAccount() {
    setWindowTitle(tr("Register Account"));

    m_urlLineEdit = new QLineEdit("http://localhost:3000");
    m_signLineEdit = new QLineEdit;
    m_nameLineEdit = new QLineEdit;
    m_emailLineEdit = new QLineEdit;
    m_passwordLineEdit = new QLineEdit;
    m_passwordLineEdit->setEchoMode(QLineEdit::Password);

    auto formLayout = new QFormLayout;
    formLayout->addRow(tr("URL:"), m_urlLineEdit);
    formLayout->addRow(tr("Sign:"), m_signLineEdit);
    formLayout->addRow(tr("Name:"), m_nameLineEdit);
    formLayout->addRow(tr("Email:"), m_emailLineEdit);
    formLayout->addRow(tr("Password:"), m_passwordLineEdit);

    setContentLayout(formLayout);
    resizeToWidth(400);
    m_signLineEdit->setFocus();
}

void RegisterAccount::accept() {

}
