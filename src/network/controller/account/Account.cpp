#include "Account.h"
#include "core/Utils.h"
#include "network/http/HttpNetwork.h"

namespace Controller {

Account::Account(HttpNetwork* httpNetwork) : m_httpNetwork(httpNetwork) {}

}

Async::Task<QString> Controller::Account::create(const CreateAccount& account) {
    QJsonObject data;
    data["login"] = account.login;
    data["full_name"] = account.fullName;
    data["email"] = account.email;
    data["password"] = Utils::sha256(account.password);

    QVariant response = co_await m_httpNetwork->post(NAME, data);
    co_return response.toMap()["token"].toString();
}

Async::Task<void> Controller::Account::update(const UpdateAccount& account) {
    QJsonObject data;
    data["full_name"] = account.fullName;

    co_await m_httpNetwork->put(NAME, data);
}

Async::Task<Controller::AbstractAccount::GetAccount> Controller::Account::get() {
    QVariant response = co_await m_httpNetwork->get(NAME);
    QVariantMap params = response.toMap();

    GetAccount account;
    account.login = params["login"].toString();
    account.email = params["email"].toString();
    account.fullName = params["full_name"].toString();

    co_return account;
}

Async::Task<QString> Controller::Account::login(const LoginAccount& account) {
    QJsonObject data;
    data["email"] = account.email;
    data["password"] = Utils::sha256(account.password);

    QVariant response = co_await m_httpNetwork->post(QString(NAME) + "/login", data);
    co_return response.toMap()["token"].toString();
}

Async::Task<void> Controller::Account::remove() {
    co_await m_httpNetwork->deleteResource(NAME);
}

Async::Task<void> Controller::Account::changePassword(const Password& password) {
    QJsonObject data;
    data["old_password"] = Utils::sha256(password.oldPassword);
    data["new_password"] = Utils::sha256(password.newPassword);

    co_await m_httpNetwork->put(QString(NAME) +  "/password", data);
}
