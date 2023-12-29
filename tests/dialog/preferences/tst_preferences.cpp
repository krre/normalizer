#include "ui/dialog/PreferencesDialog.h"
#include "settings/Settings.h"
#include <QTest>
#include <QLineEdit>

static const QUrl ApiUrl = QUrl("localhost");

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

    Server m_server;
    Account m_account;
    Project m_project;
};

class TestPreferences : public QObject {
    Q_OBJECT
private slots:
    void readSettings();
    void setSettings();
};

void TestPreferences::readSettings() {
    TestSettings settings;
    settings.m_server = TestSettings::Server(ApiUrl.toString());

    PreferencesDialog preferencesDialog(&settings);

    auto urlLineEdit = static_cast<QLineEdit*>(preferencesDialog.focusWidget());
    QCOMPARE(urlLineEdit->text(), ApiUrl.toString());
}

void TestPreferences::setSettings() {
    TestSettings settings;

    PreferencesDialog preferencesDialog(&settings);

    auto hostLineEdit = static_cast<QLineEdit*>(preferencesDialog.focusWidget());
    hostLineEdit->setText(ApiUrl.toString());

    preferencesDialog.accept();

    QCOMPARE(settings.m_server.api, ApiUrl);
}

QTEST_MAIN(TestPreferences)

#include "tst_preferences.moc"
