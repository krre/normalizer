#include "Account.h"
#include "external/network/controller/account/Account.h"

namespace Qml {

Account::Account() {
    m_account.reset(new Controller::Account(restApi()));
}

Account::~Account() {

}

}
