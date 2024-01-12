#include "Account.h"
#include "external/network/RestApi.h"

namespace Controller {

Account::Account(RestApi* restApi) : RestController(restApi) {}

QString Account::name() const {
    return "account";
}

Async::Task<Account::Token>Account::create(const CreateAccount& account) {
    QVariant response = co_await restApi()->post(endpoint(), account.serialize());
    co_return Token::parse(response);
}

Async::Task<void>Account::update(const UpdateAccount& account) {
    co_await restApi()->put(endpoint(), account.serialize());
}

Async::Task<Account::GetAccount>Account::getOne() {
    QVariant response = co_await restApi()->get(endpoint());
    co_return Account::GetAccount::parse(response);
}

Async::Task<Account::Token> Account::login(const LoginAccount& account) {
    QVariant response = co_await restApi()->post(endpoint() + "/login", account.serialize());
    co_return Token::parse(response);
}

Async::Task<void>Account::remove() {
    co_await restApi()->del(endpoint());
}

Async::Task<void>Account::changePassword(const Password& password) {
    co_await restApi()->put(endpoint() +  "/password", password.serialize());
}

}
