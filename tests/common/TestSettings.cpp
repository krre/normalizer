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

void TestSettings::setProjectLocation(const Settings::ProjectLocation& projectLocation) {
    m_projectLocation = projectLocation;
}

Settings::ProjectLocation TestSettings::projectLocation() const {
    return m_projectLocation;
}

void TestSettings::setNormLocation(const Settings::NormLocation& normLocation) {
    m_normLocation = normLocation;
}

Settings::NormLocation TestSettings::normLocation() const {
    return m_normLocation;
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
