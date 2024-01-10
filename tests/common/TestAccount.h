#pragma once
#include "external/network/controller/account/Account.h"

constexpr auto Token = "1234567890";

class TestAccount : public Controller::Account {
public:
    TestAccount();

    Async::Task<QString> create(const CreateAccount& account) override;
    Async::Task<void> update(const UpdateAccount& account) override;
    Async::Task<GetAccount> getOne() override;
    Async::Task<QString> login(const LoginAccount& account) override;
    Async::Task<void> remove() override;
    Async::Task<void> changePassword(const Password& password) override;

    CreateAccount m_createAccount;
    UpdateAccount m_updateAccount;
    Password m_password;
    LoginAccount m_loginAccount;
    GetAccount m_getAccount;
};
