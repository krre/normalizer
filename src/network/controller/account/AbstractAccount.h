#pragma once
#include "core/async/Task.h"
#include <QString>

namespace Controller {

class AbstractAccount {
public:
    struct CreateAccount {
        QString login;
        QString email;
        QString fullName;
        QString password;
    };

    struct UpdateAccount {
        QString fullName;
    };

    struct Password {
        QString oldPassword;
        QString newPassword;
    };

    struct LoginAccount {
        QString email;
        QString password;
    };

    struct GetAccount {
        QString login;
        QString email;
        QString fullName;
    };

    virtual Async::Task<QString> create(const CreateAccount& account) = 0;
    virtual Async::Task<void> update(const UpdateAccount& account) = 0;
    virtual Async::Task<GetAccount> get() = 0;
    virtual Async::Task<QString> login(const LoginAccount& account) = 0;
    virtual Async::Task<void> remove() = 0;
    virtual Async::Task<void> changePassword(const Password& password) = 0;
};

}
