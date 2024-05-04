#pragma once
#include "QmlController.h"
#include "core/async/Task.h"

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
    Async::Task<void> createImpl(const QString& login, const QString& email, const QString& fullName, const QString& password);

    QScopedPointer<Controller::Account> m_account;
};

}
