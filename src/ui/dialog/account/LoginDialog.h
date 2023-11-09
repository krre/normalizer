#pragma once
#include "ui/dialog/StandardDialog.h"
#include "core/async/Task.h"

class NetworkManager;
class QLineEdit;

class LoginDialog : public StandardDialog {
public:
    LoginDialog(NetworkManager* networkManager);
    QString token() const;

public slots:
    void accept() override;

private:
    QLineEdit* m_emailLineEdit = nullptr;
    QLineEdit* m_passwordLineEdit = nullptr;

private slots:
    void enableOkButton();
    Async::Task<void> getToken();

private:
    NetworkManager* m_networkManager = nullptr;
    QString m_token;
};
