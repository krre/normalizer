#include "FileSettingsStorage.h"
#include "core/Settings.h"

void FileSettingsStorage::setServerAddress(const ServerAddress& serverAddress) {
    Settings::setValue<Server::Host>(serverAddress.host);
    Settings::setValue<Server::Port>(serverAddress.port);
}

SettingsStorage::ServerAddress FileSettingsStorage::serverAddress() const {
    return ServerAddress(Settings::value<Server::Host>(), Settings::value<Server::Port>());
}

void FileSettingsStorage::setAccount(const Account& account) {
    Settings::setValue<::Account::Token>(account.token);
}

SettingsStorage::Account FileSettingsStorage::account() const {
    return Account(Settings::value<::Account::Token>());
}
