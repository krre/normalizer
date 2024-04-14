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

void TestSettings::setNormHost(const Settings::NormHost& normHost) {
    m_normHost = normHost;
}

Settings::NormHost TestSettings::normHost() const {
    return m_normHost;
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
