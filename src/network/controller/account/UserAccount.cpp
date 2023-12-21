#include "UserAccount.h"
#include "core/Utils.h"
#include "network/http/HttpNetwork.h"

namespace Controller {

UserAccount::UserAccount(HttpNetwork* network) : HttpController(network) {}

QString UserAccount::name() const {
    return "account";
}

Async::Task<QString>UserAccount::create(const CreateAccount& account) {
    QJsonObject data;
    data["login"] = account.login;
    data["full_name"] = account.fullName;
    data["email"] = account.email;
    data["password"] = Utils::sha256(account.password);

    QVariant response = co_await network()->post(endpoint(), data);
    co_return response.toMap()["token"].toString();
}

Async::Task<void>UserAccount::update(const UpdateAccount& account) {
    QJsonObject data;
    data["full_name"] = account.fullName;

    co_await network()->put(endpoint(), data);
}

Async::Task<Account::GetAccount>UserAccount::getOne() {
    QVariant response = co_await network()->get(endpoint());
    QVariantMap params = response.toMap();

    GetAccount account;
    account.login = params["login"].toString();
    account.email = params["email"].toString();
    account.fullName = params["full_name"].toString();

    co_return account;
}

Async::Task<QString>UserAccount::login(const LoginAccount& account) {
    QJsonObject data;
    data["email"] = account.email;
    data["password"] = Utils::sha256(account.password);

    QVariant response = co_await network()->post(endpoint() + "/login", data);
    co_return response.toMap()["token"].toString();
}

Async::Task<void>UserAccount::remove() {
    co_await network()->deleteResource(endpoint());
}

Async::Task<void>UserAccount::changePassword(const Password& password) {
    QJsonObject data;
    data["old_password"] = Utils::sha256(password.oldPassword);
    data["new_password"] = Utils::sha256(password.newPassword);

    co_await network()->put(endpoint() +  "/password", data);
}

}
