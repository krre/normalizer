#include "Account.h"
#include "external/network/RestApi.h"

namespace Controller {

Account::Account(RestApi* restApi) : RestController(restApi) {}

QString Account::name() const {
    return "account";
}

Async::Task<Account::Response::Token> Account::create(const Request::Create& params) {
    QVariant response = co_await restApi()->post(endpoint(), params.serialize());
    co_return Response::Token::deserialize(response);
}

Async::Task<void> Account::update(const Request::Update& params) {
    co_await restApi()->put(endpoint(), params.serialize());
}

Async::Task<Account::Response::Get> Account::getOne() {
    QVariant response = co_await restApi()->get(endpoint());
    co_return Response::Get::deserialize(response);
}

Async::Task<Account::Response::Token> Account::login(const Request::Login& params) {
    QVariant response = co_await restApi()->post(endpoint() + "/login", params.serialize());
    co_return Response::Token::deserialize(response);
}

Async::Task<void> Account::remove() {
    co_await restApi()->del(endpoint());
}

Async::Task<void> Account::changePassword(const Request::Password& params) {
    co_await restApi()->put(endpoint() +  "/password", params.serialize());
}

}
