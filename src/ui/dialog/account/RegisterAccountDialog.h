#pragma once
#include "ui/dialog/StandardDialog.h"
#include "core/async/Task.h"

class AbstractNetworkManager;

class QLineEdit;

class RegisterAccountDialog : public StandardDialog {
public:
    RegisterAccountDialog(AbstractNetworkManager* networkManager);
    QString token() const;

public slots:
    void accept() override;

private:
    QLineEdit* m_signLineEdit = nullptr;
    QLineEdit* m_nameLineEdit = nullptr;
    QLineEdit* m_emailLineEdit = nullptr;
    QLineEdit* m_passwordLineEdit = nullptr;
    QLineEdit* m_confirmPasswordLineEdit = nullptr;

private slots:
    void enableOkButton();
    Async::Task<void> getToken();

private:
    AbstractNetworkManager* m_networkManager = nullptr;
    QString m_token;
};
