#pragma once
#include "external/network/controller/RestController.h"
#include "core/async/Task.h"
#include "core/Utils.h"
#include <QVariant>

class RestApi;

namespace Controller {

class Account : public RestController {
public:
    struct Request {
        struct Create {
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

        struct Update {
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

        struct Login {
            QString email;
            QString password;

            QVariant serialize() const {
                return QVariantMap({
                    { "email", email },
                    { "password", Utils::sha256(password) },
                });
            }
        };
    };

    struct Response {
        struct Token {
            QString token;

            static Token deserialize(const QVariant& value) {
                QVariantMap params = value.toMap();

                Token result;
                result.token = params["token"].toString();

                return result;
            }
        };

        struct Get {
            QString login;
            QString email;
            QString fullName;

            static Get deserialize(const QVariant& value) {
                QVariantMap params = value.toMap();

                Get result;
                result.login = params["login"].toString();
                result.email = params["email"].toString();
                result.fullName = params["full_name"].toString();

                return result;
            }
        };
    };

    Account(RestApi* restApi);

    QString name() const override;

    Async::Task<Response::Token> create(const Request::Create& params);
    Async::Task<void> update(const Request::Update& params);
    Async::Task<Response::Get> getOne();
    Async::Task<Response::Token> login(const Request::Login& params);
    Async::Task<void> remove();
    Async::Task<void> changePassword(const Request::Password& params);
};

}
