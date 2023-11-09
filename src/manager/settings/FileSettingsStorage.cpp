#include "FileSettingsStorage.h"
#include "core/Settings.h"

FileSettingsStorage::FileSettingsStorage() {
    Settings::init();
}

void FileSettingsStorage::setMainWindow(const MainWindow& mainWindow) {
    Settings::setValue<::MainWindow::Geometry>(mainWindow.geometry);
    Settings::setValue<::MainWindow::State>(mainWindow.state);
}

SettingsStorage::MainWindow FileSettingsStorage::mainWindow() const {
    return MainWindow(Settings::value<::MainWindow::Geometry>(), Settings::value<::MainWindow::State>());
}

bool FileSettingsStorage::containsMainWindow() const {
    return Settings::contains<::MainWindow::Geometry>();
}

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
