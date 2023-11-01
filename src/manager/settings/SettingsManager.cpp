#include "SettingsManager.h"
#include "core/Settings.h"

void SettingsManager::setServerAddress(const ServerAddress& serverAddress) {
    Settings::setValue<Server::Host>(serverAddress.host);
    Settings::setValue<Server::Port>(serverAddress.port);
}

AbstractSettingsManager::ServerAddress SettingsManager::serverAddress() const {
    return ServerAddress(Settings::value<Server::Host>(), Settings::value<Server::Port>());
}

void SettingsManager::setAccount(const Account& account) {
    Settings::setValue<::Account::Token>(account.token);
}

AbstractSettingsManager::Account SettingsManager::account() const {
    return Account(Settings::value<::Account::Token>());
}
