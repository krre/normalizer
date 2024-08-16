#include "TestSettings.h"

Settings::MainWindow TestSettings::mainWindow() const {
    return Settings::MainWindow();
}

void TestSettings::setAccount(const Settings::Account& account) {
    m_account = account;
}

Settings::Account TestSettings::account() const {
    return m_account;
}

void TestSettings::setDevelopmentServer(const Settings::DevelopmentServer& developmentServer) {
    m_developmentServer = developmentServer;
}

Settings::DevelopmentServer TestSettings::developmentServer() const {
    return m_developmentServer;
}

void TestSettings::setProjectTable(const Settings::ProjectTable& projectTable) {
    m_projectTable = projectTable;
}

Settings::ProjectTable TestSettings::projectTable() const {
    return m_projectTable;
}

void TestSettings::setEditor(const Editor& editor) {
    m_editor = editor;
}

Settings::Editor TestSettings::editor() const {
    return m_editor;
}

void TestSettings::setGraphics(const Graphics& graphics) {
    m_graphics = graphics;
}

Settings::Graphics TestSettings::graphics() const {
    return m_graphics;
}
