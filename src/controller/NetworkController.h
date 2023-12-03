#pragma once
#include <QJsonObject>

class NetworkManager;

namespace Controller {

// template <typename T>
// class Request {
// public:
//     QJsonObject serialize()

// private:
//     T data;
// };

// template <typename T>
// class Response {

// private:
    // T data;
// };

class NetworkController {
public:
    NetworkController(NetworkManager* networkManager);

    virtual QString name() const = 0;
    NetworkManager* networkManager() const;

    // Async::Task<QString> create(const User& user);
    // Async::Task<void> update(const User& user);
    // Async::Task<User> getOne();
    // Async::Task<User> getList();
    // Async::Task<void> remove();

private:
    NetworkManager* m_networkManager = nullptr;
};

}
