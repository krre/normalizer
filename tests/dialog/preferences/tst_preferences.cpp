#include "ui/dialog/PreferencesDialog.h"
#include "manager/settings/SettingsStorage.h"
#include <QTest>
#include <QLineEdit>

static const QHostAddress host = QHostAddress(QHostAddress::LocalHost);
constexpr auto port = 3128;

class TestSettingsStorage : public SettingsStorage {
public:
    void setMainWindow(const MainWindow& mainWindow [[maybe_unused]]) override {}

    SettingsStorage::MainWindow mainWindow() const override {
        return MainWindow();
    }

    bool containsMainWindow() const override {
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
    TestSettingsStorage settingsStorage;
    settingsStorage.m_serverAddress = TestSettingsStorage::ServerAddress(host.toString(), port);

    PreferencesDialog preferencesDialog(&settingsStorage);

    QLineEdit* hostLineEdit = static_cast<QLineEdit*>(preferencesDialog.focusWidget());
    QCOMPARE(hostLineEdit->text(), host.toString());

    QTest::keyClick(&preferencesDialog, Qt::Key_Tab);

    QLineEdit* portLineEdit = static_cast<QLineEdit*>(preferencesDialog.focusWidget());
    QCOMPARE(portLineEdit->text().toInt(), port);
}

void TestPreferences::setSettings() {
    TestSettingsStorage settingsStorage;

    PreferencesDialog preferencesDialog(&settingsStorage);

    QLineEdit* hostLineEdit = static_cast<QLineEdit*>(preferencesDialog.focusWidget());
    hostLineEdit->setText(host.toString());

    QTest::keyClick(&preferencesDialog, Qt::Key_Tab);

    QLineEdit* portLineEdit = static_cast<QLineEdit*>(preferencesDialog.focusWidget());
    portLineEdit->setText(QString::number(port));

    preferencesDialog.accept();

    QCOMPARE(settingsStorage.m_serverAddress.host, host.toString());
    QCOMPARE(settingsStorage.m_serverAddress.port, port);
}

QTEST_MAIN(TestPreferences)

#include "tst_preferences.moc"
