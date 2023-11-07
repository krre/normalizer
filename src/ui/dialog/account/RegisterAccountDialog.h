#pragma once
#include "ui/dialog/StandardDialog.h"
#include "core/async/Task.h"

class NetworkManager;
class QLineEdit;

class RegisterAccountDialog : public StandardDialog {
public:
    RegisterAccountDialog(NetworkManager* networkManager);
    QString token() const;

public slots:
    void accept() override;

private:
    QLineEdit* m_loginLineEdit = nullptr;
    QLineEdit* m_fullNameLineEdit = nullptr;
    QLineEdit* m_emailLineEdit = nullptr;
    QLineEdit* m_passwordLineEdit = nullptr;
    QLineEdit* m_confirmPasswordLineEdit = nullptr;

private slots:
    void enableOkButton();
    Async::Task<void> getToken();

private:
    void errorMessage(const QString& message);

    NetworkManager* m_networkManager = nullptr;
    QString m_token;
};
