#pragma once
#include "QmlController.h"

namespace Controller {
    class Account;
}

namespace Qml {

class Account : public QmlController {
    Q_OBJECT
public:
    Account();
    ~Account();

    Q_INVOKABLE void create(const QString& login, const QString& email, const QString& fullName, const QString& password);

private:
    QScopedPointer<Controller::Account> m_account;
};

}
