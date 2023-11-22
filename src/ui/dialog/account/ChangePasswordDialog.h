#pragma once
#include "ui/dialog/StandardDialog.h"

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
    NetworkManager* m_networkManager = nullptr;

    QLineEdit* m_oldPasswordLineEdit = nullptr;
    QLineEdit* m_newPasswordLineEdit = nullptr;
    QLineEdit* m_confirmPasswordLineEdit = nullptr;
};
