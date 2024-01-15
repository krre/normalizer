#include "Account.h"
#include "external/network/RestApi.h"

namespace Controller {

Account::Account(RestApi* restApi) : RestController(restApi) {}

QString Account::name() const {
    return "account";
}

Async::Task<Account::Token>Account::create(const CreateParams& params) {
    QVariant response = co_await restApi()->post(endpoint(), params.serialize());
    co_return Token::parse(response);
}

Async::Task<void>Account::update(const UpdateParams& params) {
    co_await restApi()->put(endpoint(), params.serialize());
}

Async::Task<Account::GetParams>Account::getOne() {
    QVariant response = co_await restApi()->get(endpoint());
    co_return GetParams::parse(response);
}

Async::Task<Account::Token> Account::login(const LoginParams& params) {
    QVariant response = co_await restApi()->post(endpoint() + "/login", params.serialize());
    co_return Token::parse(response);
}

Async::Task<void>Account::remove() {
    co_await restApi()->del(endpoint());
}

Async::Task<void>Account::changePassword(const PasswordParams& params) {
    co_await restApi()->put(endpoint() +  "/password", params.serialize());
}

}
