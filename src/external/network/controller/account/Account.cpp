#include "Account.h"
#include "external/network/RestApi.h"

namespace Controller {

Account::Account(RestApi* restApi) : RestController(restApi) {}

QString Account::name() const {
    return "account";
}

Async::Task<Account::TokenResponse>Account::create(const CreateRequest& params) {
    QVariant response = co_await restApi()->post(endpoint(), params.serialize());
    co_return TokenResponse::deserialize(response);
}

Async::Task<void>Account::update(const UpdateRequest& params) {
    co_await restApi()->put(endpoint(), params.serialize());
}

Async::Task<Account::GetResponse>Account::getOne() {
    QVariant response = co_await restApi()->get(endpoint());
    co_return GetResponse::deserialize(response);
}

Async::Task<Account::TokenResponse> Account::login(const LoginRequest& params) {
    QVariant response = co_await restApi()->post(endpoint() + "/login", params.serialize());
    co_return TokenResponse::deserialize(response);
}

Async::Task<void>Account::remove() {
    co_await restApi()->del(endpoint());
}

Async::Task<void>Account::changePassword(const PasswordRequest& params) {
    co_await restApi()->put(endpoint() +  "/password", params.serialize());
}

}
