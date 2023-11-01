#include "RegisterAccountDialog.h"
#include "core/async/NetworkAccessManager.h"
#include "core/Constants.h"
#include "core/Settings.h"
#include <QtWidgets>
#include <QNetworkReply>

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
    QJsonObject data;
    data["sign"] = m_signLineEdit->text();
    data["name"] = m_nameLineEdit->text();
    data["email"] = m_emailLineEdit->text();
    data["password"] = m_passwordLineEdit->text();

    QNetworkRequest request(QUrl(m_urlLineEdit->text() + "/users"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    Async::NetworkAccessManager networkAccessManager;
    QNetworkReply* reply = co_await networkAccessManager.post(request, QJsonDocument(data).toJson(QJsonDocument::Compact));

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray response = reply->readAll();
        QString token = QJsonDocument::fromJson(response).object()["token"].toString();
        Settings::setValue<Account::Token>(token);
        StandardDialog::accept();
    } else {
        QString message;
        QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

        if (statusCode.toInt() == Const::HttpStatus::Conflict) {
            message = tr("Account already exists");
        } else {
            message = reply->errorString();
        }

        QMessageBox::critical(this, tr("Register error"), message);
    }
}
