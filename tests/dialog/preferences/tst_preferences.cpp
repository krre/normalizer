#include "ui/dialog/PreferencesDialog.h"
#include "manager/settings/Settings.h"
#include <QTest>
#include <QLineEdit>

static const QUrl Url = QUrl("localhost");

class TestSettings : public Settings {
public:
    void setMainWindow(const MainWindow& mainWindow [[maybe_unused]]) override {}

    Settings::MainWindow mainWindow() const override {
        return MainWindow();
    }

    bool containsGeometry() const override {
        return true;
    }

    void setServerAddress(const ServerAddress& serverAddress) override {
        m_serverAddress = serverAddress;
    }

    ServerAddress serverAddress() const override {
        return m_serverAddress;
    }

    void setAccount(const Account& account) override {
        m_account = account;
    }

    Account account() const override {
        return m_account;
    }

    ServerAddress m_serverAddress;
    Account m_account;
};

class TestPreferences : public QObject {
    Q_OBJECT
private slots:
    void readSettings();
    void setSettings();
};

void TestPreferences::readSettings() {
    TestSettings settings;
    settings.m_serverAddress = TestSettings::ServerAddress(Url.toString());

    PreferencesDialog preferencesDialog(&settings);

    auto urlLineEdit = static_cast<QLineEdit*>(preferencesDialog.focusWidget());
    QCOMPARE(urlLineEdit->text(), Url.toString());
}

void TestPreferences::setSettings() {
    TestSettings settings;

    PreferencesDialog preferencesDialog(&settings);

    auto hostLineEdit = static_cast<QLineEdit*>(preferencesDialog.focusWidget());
    hostLineEdit->setText(Url.toString());

    preferencesDialog.accept();

    QCOMPARE(settings.m_serverAddress.url, Url);
}

QTEST_MAIN(TestPreferences)

#include "tst_preferences.moc"
