#include "UserAccount.h"
#include "external/network/http/HttpNetwork.h"

namespace Controller {

UserAccount::UserAccount(HttpNetwork* network) : HttpController(network) {}

QString UserAccount::name() const {
    return "account";
}

Async::Task<QString>UserAccount::create(const CreateAccount& account) {
    QVariant response = co_await network()->post(endpoint(), account.serialize());
    co_return response.toMap()["token"].toString();
}

Async::Task<void>UserAccount::update(const UpdateAccount& account) {
    co_await network()->put(endpoint(), account.serialize());
}

Async::Task<Account::GetAccount>UserAccount::getOne() {
    QVariant response = co_await network()->get(endpoint());
    QVariantMap params = response.toMap();
    co_return Account::GetAccount::fromVariantMap(params);
}

Async::Task<QString>UserAccount::login(const LoginAccount& account) {
    QVariant response = co_await network()->post(endpoint() + "/login", account.serialize());
    co_return response.toMap()["token"].toString();
}

Async::Task<void>UserAccount::remove() {
    co_await network()->deleteResource(endpoint());
}

Async::Task<void>UserAccount::changePassword(const Password& password) {
    co_await network()->put(endpoint() +  "/password", password.serialize());
}

}
