#include "Account.h"
#include "external/network/controller/account/Account.h"

namespace Qml {

Account::Account() {
    m_account.reset(new Controller::Account(restApi()));
}

Account::~Account() {

}

void Account::create(const QString& login, const QString& email, const QString& fullName, const QString& password) {
    createImpl(login, email, fullName, password);
}

Async::Task<void> Account::createImpl(const QString& login, const QString& email, const QString& fullName, const QString& password) {
    Controller::Account::Request::Create params;
    params.login = login;
    params.email = email;
    params.fullName = fullName;
    params.password = password;

    try {
        co_await m_account->create(params);
    } catch (RestException& e) {
        QString message = e.status() == RestStatus::Conflict ? tr("Account already exists") : e.message();
        emit errorOccured(e.status(), message);
    }
}

}
