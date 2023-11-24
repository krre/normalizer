#include "TestNetworkManager.h"

Async::Task<QString> TestNetworkManager::createUser(const User& user) {
    m_user = user;
    co_return Token;
}

Async::Task<void> TestNetworkManager::updateUser(const User& user) {
    co_return;
}

Async::Task<NetworkManager::User> TestNetworkManager::getUser() {
    User user;
    co_return user;
}

Async::Task<QString> TestNetworkManager::login(const User& user) {
    m_user = user;
    co_return Token;
}

Async::Task<void> TestNetworkManager::deleteUser() {
    co_return;
}

Async::Task<void> TestNetworkManager::changePassword(const UserPassword& userPassword) {
    m_userPassword = userPassword;
    co_return;
}
