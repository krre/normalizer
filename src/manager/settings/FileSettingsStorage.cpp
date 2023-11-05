#include "FileSettingsStorage.h"
#include "core/Settings.h"

void FileSettingsStrorage::setServerAddress(const ServerAddress& serverAddress) {
    Settings::setValue<Server::Host>(serverAddress.host);
    Settings::setValue<Server::Port>(serverAddress.port);
}

SettingsStorage::ServerAddress FileSettingsStrorage::serverAddress() const {
    return ServerAddress(Settings::value<Server::Host>(), Settings::value<Server::Port>());
}

void FileSettingsStrorage::setAccount(const Account& account) {
    Settings::setValue<::Account::Token>(account.token);
}

SettingsStorage::Account FileSettingsStrorage::account() const {
    return Account(Settings::value<::Account::Token>());
}
