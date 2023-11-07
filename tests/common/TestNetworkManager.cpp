#include "TestNetworkManager.h"

Async::Task<QString> TestNetworkManager::createUser(const User& user) {
    m_user = user;
    co_return Token;
}

Async::Task<QString> TestNetworkManager::login(const User& user) {
    m_user = user;
    co_return Token;
}
