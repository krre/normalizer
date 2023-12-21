#include "TestAccount.h"

TestAccount::TestAccount() {}


Async::Task<QString> TestAccount::create(const CreateAccount& account) {
    m_createAccount = account;
    co_return Token;
}

Async::Task<void> TestAccount::update(const UpdateAccount& account) {
    m_updateAccount = account;
    co_return;
}

Async::Task<Controller::Account::GetAccount> TestAccount::getOne() {
    co_return m_getAccount;
}

Async::Task<QString> TestAccount::login(const LoginAccount& account) {
    m_loginAccount = account;
    co_return Token;
}

Async::Task<void> TestAccount::remove() {
    co_return;
}

Async::Task<void> TestAccount::changePassword(const Password& password) {
    m_password = password;
    co_return;
}
