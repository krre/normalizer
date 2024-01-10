#pragma once
#include "core/async/Task.h"
#include "core/Utils.h"
#include <QString>
#include <QJsonObject>

namespace Controller {

class Account {
public:
    struct CreateAccount {
        QString login;
        QString email;
        QString fullName;
        QString password;

        QJsonObject serialize() const {
            return {
                { "login", login },
                { "email", email },
                { "full_name", fullName },
                { "password", Utils::sha256(password) },
            };
        }
    };

    struct UpdateAccount {
        QString fullName;

        QJsonObject serialize() const {
            return {
                { "full_name", fullName },
            };
        }
    };

    struct Password {
        QString oldPassword;
        QString newPassword;

        QJsonObject serialize() const {
            return {
                { "old_password", Utils::sha256(oldPassword) },
                { "new_password", Utils::sha256(newPassword) },
            };
        }
    };

    struct LoginAccount {
        QString email;
        QString password;

        QJsonObject serialize() const {
            return {
                { "email", email },
                { "password", Utils::sha256(password) },
            };
        }
    };

    struct GetAccount {
        QString login;
        QString email;
        QString fullName;

        static GetAccount fromVariantMap(const QVariantMap& params) {
            GetAccount result;
            result.login = params["login"].toString();
            result.email = params["email"].toString();
            result.fullName = params["full_name"].toString();

            return result;
        }
    };

    virtual Async::Task<QString> create(const CreateAccount& account) = 0;
    virtual Async::Task<void> update(const UpdateAccount& account) = 0;
    virtual Async::Task<GetAccount> getOne() = 0;
    virtual Async::Task<QString> login(const LoginAccount& account) = 0;
    virtual Async::Task<void> remove() = 0;
    virtual Async::Task<void> changePassword(const Password& password) = 0;
};

}
