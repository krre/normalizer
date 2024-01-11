#include "UserAccount.h"
#include "external/network/http/HttpRestApi.h"

namespace Controller {

UserAccount::UserAccount(HttpRestApi* network) : RestController(network) {}

QString UserAccount::name() const {
    return "account";
}

Async::Task<Account::Token>UserAccount::create(const CreateAccount& account) {
    QVariant response = co_await network()->post(endpoint(), account.serialize());
    co_return Token::parse(response);
}

Async::Task<void>UserAccount::update(const UpdateAccount& account) {
    co_await network()->put(endpoint(), account.serialize());
}

Async::Task<Account::GetAccount>UserAccount::getOne() {
    QVariant response = co_await network()->get(endpoint());
    co_return Account::GetAccount::parse(response);
}

Async::Task<Account::Token> UserAccount::login(const LoginAccount& account) {
    QVariant response = co_await network()->post(endpoint() + "/login", account.serialize());
    co_return Token::parse(response);
}

Async::Task<void>UserAccount::remove() {
    co_await network()->del(endpoint());
}

Async::Task<void>UserAccount::changePassword(const Password& password) {
    co_await network()->put(endpoint() +  "/password", password.serialize());
}

}
