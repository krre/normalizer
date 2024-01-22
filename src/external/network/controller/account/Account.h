#pragma once
#include "external/network/controller/RestController.h"
#include "core/async/Task.h"
#include "core/Utils.h"
#include <QVariant>

class RestApi;

namespace Controller {

class Account : public RestController {
public:
    struct CreateRequest {
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

    struct UpdateRequest {
        QString fullName;

        QVariant serialize() const {
            return QVariantMap({
                { "full_name", fullName },
            });
        }
    };

    struct PasswordRequest {
        QString oldPassword;
        QString newPassword;

        QVariant serialize() const {
            return QVariantMap({
                { "old_password", Utils::sha256(oldPassword) },
                { "new_password", Utils::sha256(newPassword) },
            });
        }
    };

    struct LoginRequest {
        QString email;
        QString password;

        QVariant serialize() const {
            return QVariantMap({
                { "email", email },
                { "password", Utils::sha256(password) },
            });
        }
    };

    struct TokenResponse {
        QString token;

        static TokenResponse deserialize(const QVariant& value) {
            QVariantMap params = value.toMap();

            TokenResponse result;
            result.token = params["token"].toString();

            return result;
        }
    };

    struct GetResponse {
        QString login;
        QString email;
        QString fullName;

        static GetResponse deserialize(const QVariant& value) {
            QVariantMap params = value.toMap();

            GetResponse result;
            result.login = params["login"].toString();
            result.email = params["email"].toString();
            result.fullName = params["full_name"].toString();

            return result;
        }
    };

    Account(RestApi* restApi);

    QString name() const override;

    Async::Task<TokenResponse> create(const CreateRequest& params);
    Async::Task<void> update(const UpdateRequest& params);
    Async::Task<GetResponse> getOne();
    Async::Task<TokenResponse> login(const LoginRequest& params);
    Async::Task<void> remove();
    Async::Task<void> changePassword(const PasswordRequest& params);
};

}
