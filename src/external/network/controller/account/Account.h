#pragma once
#include "external/network/controller/RestController.h"
#include "core/async/Task.h"
#include "core/Utils.h"
#include <QVariant>

class RestApi;

namespace Controller {

class Account : public RestController {
public:
    struct Token {
        QString token;

        static Token parse(const QVariant& value) {
            QVariantMap params = value.toMap();

            Token result;
            result.token = params["token"].toString();

            return result;
        }
    };

    struct CreateAccount {
        QString login;
        QString email;
        QString fullName;
        QString password;

        QVariant serialize() const {
            return QVariantMap({
                { "login", login },
                { "email", email },
                { "full_name", fullName },
                { "password", Utils::sha256(password) },
            });
        }
    };

    struct UpdateAccount {
        QString fullName;

        QVariant serialize() const {
            return QVariantMap({
                { "full_name", fullName },
            });
        }
    };

    struct Password {
        QString oldPassword;
        QString newPassword;

        QVariant serialize() const {
            return QVariantMap({
                { "old_password", Utils::sha256(oldPassword) },
                { "new_password", Utils::sha256(newPassword) },
            });
        }
    };

    struct LoginAccount {
        QString email;
        QString password;

        QVariant serialize() const {
            return QVariantMap({
                { "email", email },
                { "password", Utils::sha256(password) },
            });
        }
    };

    struct GetAccount {
        QString login;
        QString email;
        QString fullName;

        static GetAccount parse(const QVariant& value) {
            QVariantMap params = value.toMap();

            GetAccount result;
            result.login = params["login"].toString();
            result.email = params["email"].toString();
            result.fullName = params["full_name"].toString();

            return result;
        }
    };

    Account(RestApi* restApi);

    QString name() const override;

    Async::Task<Token> create(const CreateAccount& account);
    Async::Task<void> update(const UpdateAccount& account);
    Async::Task<GetAccount> getOne();
    Async::Task<Token> login(const LoginAccount& account);
    Async::Task<void> remove();
    Async::Task<void> changePassword(const Password& password);
};

}
