#pragma once
#include "ui/dialog/StandardDialog.h"
#include "core/async/Task.h"

class NetworkManager;
class QLineEdit;

class ProfileDialog : public StandardDialog {
public:
    ProfileDialog(NetworkManager* networkManager);

public slots:
    void accept() override;

private slots:
    void openChangePasswordDialog();

    Async::Task<void> deleteAccount();
    Async::Task<void> getProfile();
    Async::Task<void> updateProfile();

private:
    NetworkManager* m_networkManager = nullptr;

    QLineEdit* m_loginLineEdit = nullptr;
    QLineEdit* m_fullNameLineEdit = nullptr;
    QLineEdit* m_emailLineEdit = nullptr;
};
