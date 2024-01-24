#include "ui/dialog/PreferencesDialog.h"
#include "external/settings/Settings.h"
#include <QTest>
#include <QLineEdit>

static const QUrl ApiUrl = QUrl("localhost/api");

class TestSettings : public Settings {
public:
    void setMainWindow(const MainWindow& mainWindow [[maybe_unused]]) override {}

    Settings::MainWindow mainWindow() const override {
        return MainWindow();
    }

    bool containsGeometry() const override {
        return true;
    }

    void setServer(const Server& server) override {
        m_server = server;
    }

    Server server() const override {
        return m_server;
    }

    void setAccount(const Account& account) override {
        m_account = account;
    }

    Account account() const override {
        return m_account;
    }

    void setProject(const Project& project) override {
        m_project = project;
    }

    Project project() const override {
        return m_project;
    }

    void setProjectTable(const ProjectTable& projectTable) override {
        m_projectTable = projectTable;
    }

    ProjectTable projectTable() const override {
        return m_projectTable;
    }

    void setEditor(const Editor& editor) override {
        m_editor = editor;
    }

    Editor editor() const override {
        return m_editor;
    }

    Server m_server;
    Account m_account;
    Project m_project;
    ProjectTable m_projectTable;
    Editor m_editor;
};

class TestPreferences : public QObject {
    Q_OBJECT
private slots:
    void readSettings();
    void setSettings();
};

void TestPreferences::readSettings() {
    Settings::Server server;
    server.api = ApiUrl.toString();

    TestSettings settings;
    settings.m_server = server;

    PreferencesDialog preferencesDialog(&settings);
    auto apiLineEdit = static_cast<QLineEdit*>(preferencesDialog.focusWidget());

    QCOMPARE(apiLineEdit->text(), ApiUrl.toString());
}

void TestPreferences::setSettings() {
    TestSettings settings;

    PreferencesDialog preferencesDialog(&settings);

    auto apiLineEdit = static_cast<QLineEdit*>(preferencesDialog.focusWidget());
    apiLineEdit->setText(ApiUrl.toString());
    preferencesDialog.accept();

    QCOMPARE(settings.m_server.api, ApiUrl);
}

QTEST_MAIN(TestPreferences)

#include "tst_preferences.moc"
