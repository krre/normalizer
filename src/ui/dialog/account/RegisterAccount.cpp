#include "RegisterAccount.h"
#include <QtWidgets>

RegisterAccount::RegisterAccount() {
    setWindowTitle(tr("Register Account"));

    m_urlLineEdit = new QLineEdit("http://localhost:3000");
    connect(m_urlLineEdit, &QLineEdit::textChanged, this, &RegisterAccount::enableOkButton);

    m_signLineEdit = new QLineEdit;
    connect(m_signLineEdit, &QLineEdit::textChanged, this, &RegisterAccount::enableOkButton);

    m_nameLineEdit = new QLineEdit;
    connect(m_nameLineEdit, &QLineEdit::textChanged, this, &RegisterAccount::enableOkButton);

    m_emailLineEdit = new QLineEdit;
    connect(m_emailLineEdit, &QLineEdit::textChanged, this, &RegisterAccount::enableOkButton);

    m_passwordLineEdit = new QLineEdit;
    m_passwordLineEdit->setEchoMode(QLineEdit::Password);
    connect(m_passwordLineEdit, &QLineEdit::textChanged, this, &RegisterAccount::enableOkButton);

    auto formLayout = new QFormLayout;
    formLayout->addRow(tr("URL:"), m_urlLineEdit);
    formLayout->addRow(tr("Sign:"), m_signLineEdit);
    formLayout->addRow(tr("Name:"), m_nameLineEdit);
    formLayout->addRow(tr("Email:"), m_emailLineEdit);
    formLayout->addRow(tr("Password:"), m_passwordLineEdit);

    setContentLayout(formLayout);
    resizeToWidth(400);
    m_signLineEdit->setFocus();
    enableOkButton();
}

void RegisterAccount::accept() {

}

void RegisterAccount::enableOkButton() {
    buttonBox()->button(QDialogButtonBox::Ok)->setEnabled(!m_urlLineEdit->text().isEmpty() &&
                                                          !m_signLineEdit->text().isEmpty() &&
                                                          !m_nameLineEdit->text().isEmpty() &&
                                                          !m_emailLineEdit->text().isEmpty() &&
                                                          !m_passwordLineEdit->text().isEmpty());
}
