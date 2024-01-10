#include "TestAccount.h"

TestAccount::TestAccount() {}


Async::Task<Controller::Account::Token> TestAccount::create(const CreateAccount& account) {
    m_createAccount = account;

    Controller::Account::Token result;
    result.token = AccountToken;

    co_return result;
}

Async::Task<void> TestAccount::update(const UpdateAccount& account) {
    m_updateAccount = account;
    co_return;
}

Async::Task<Controller::Account::GetAccount> TestAccount::getOne() {
    co_return m_getAccount;
}

Async::Task<Controller::Account::Token> TestAccount::login(const LoginAccount& account) {
    m_loginAccount = account;

    Controller::Account::Token result;
    result.token = AccountToken;

    co_return result;
}

Async::Task<void> TestAccount::remove() {
    co_return;
}

Async::Task<void> TestAccount::changePassword(const Password& password) {
    m_password = password;
    co_return;
}
