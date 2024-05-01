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

private:
    QScopedPointer<Controller::Account> m_account;
};

}
