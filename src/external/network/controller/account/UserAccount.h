#pragma once
#include "external/network/controller/HttpController.h"
#include "Account.h"

namespace Controller {

class UserAccount : public HttpController, public Account {
public:
    UserAccount(HttpNetwork* network);
    QString name() const override;

    Async::Task<Token> create(const CreateAccount& account) override;
    Async::Task<void> update(const UpdateAccount& account) override;
    Async::Task<GetAccount> getOne() override;
    Async::Task<Token> login(const LoginAccount& account) override;
    Async::Task<void> remove() override;
    Async::Task<void> changePassword(const Password& password) override;
};

}
