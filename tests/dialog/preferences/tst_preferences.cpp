#include "ui/dialog/PreferencesDialog.h"
#include "manager/settings/SettingsStorage.h"
#include <QTest>
#include <QLineEdit>

static const QHostAddress Host = QHostAddress(QHostAddress::LocalHost);
constexpr auto Port = 3128;

class TestSettingsStorage : public SettingsStorage {
public:
    void setMainWindow(const MainWindow& mainWindow [[maybe_unused]]) override {}

    SettingsStorage::MainWindow mainWindow() const override {
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
    TestSettingsStorage settingsStorage;
    settingsStorage.m_serverAddress = TestSettingsStorage::ServerAddress(Host.toString(), Port);

    PreferencesDialog preferencesDialog(&settingsStorage);

    auto hostLineEdit = static_cast<QLineEdit*>(preferencesDialog.focusWidget());
    QCOMPARE(hostLineEdit->text(), Host.toString());

    QTest::keyClick(&preferencesDialog, Qt::Key_Tab);
    auto portLineEdit = static_cast<QLineEdit*>(preferencesDialog.focusWidget());
    QCOMPARE(portLineEdit->text().toInt(), Port);
}

void TestPreferences::setSettings() {
    TestSettingsStorage settingsStorage;

    PreferencesDialog preferencesDialog(&settingsStorage);

    auto hostLineEdit = static_cast<QLineEdit*>(preferencesDialog.focusWidget());
    hostLineEdit->setText(Host.toString());

    QTest::keyClick(&preferencesDialog, Qt::Key_Tab);
    auto portLineEdit = static_cast<QLineEdit*>(preferencesDialog.focusWidget());
    portLineEdit->setText(QString::number(Port));

    preferencesDialog.accept();

    QCOMPARE(settingsStorage.m_serverAddress.host, Host.toString());
    QCOMPARE(settingsStorage.m_serverAddress.port, Port);
}

QTEST_MAIN(TestPreferences)

#include "tst_preferences.moc"
