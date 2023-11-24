#pragma once
#include "ui/dialog/StandardDialog.h"
#include "core/async/Task.h"

class NetworkManager;
class QLineEdit;

class ChangePasswordDialog : public StandardDialog {
public:
    ChangePasswordDialog(NetworkManager* networkManager);

public slots:
    void accept() override;

private slots:
    void enableOkButton();

private:
    Async::Task<void> changePassword();

    NetworkManager* m_networkManager = nullptr;

    QLineEdit* m_oldPasswordLineEdit = nullptr;
    QLineEdit* m_newPasswordLineEdit = nullptr;
    QLineEdit* m_confirmPasswordLineEdit = nullptr;
};
