#include "ui/dialog/PreferencesDialog.h"
#include "manager/settings/AbstractSettingsManager.h"
#include <QTest>
#include <QLineEdit>

static const QHostAddress host = QHostAddress(QHostAddress::LocalHost);
constexpr auto port = 3128;

class TestSettingsManager : public AbstractSettingsManager {
public:
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
    TestSettingsManager settingsManager;
    settingsManager.m_serverAddress = TestSettingsManager::ServerAddress(host.toString(), port);

    PreferencesDialog preferencesDialog(&settingsManager);

    QCOMPARE(preferencesDialog.m_hostLineEdit->text(), host.toString());
    QCOMPARE(preferencesDialog.m_portLineEdit->text().toInt(), port);
}

void TestPreferences::setSettings() {
    TestSettingsManager settingsManager;

    PreferencesDialog preferencesDialog(&settingsManager);
    preferencesDialog.m_hostLineEdit->setText(host.toString());
    preferencesDialog.m_portLineEdit->setText(QString::number(port));
    preferencesDialog.accept();

    QCOMPARE(settingsManager.m_serverAddress.host, host.toString());
    QCOMPARE(settingsManager.m_serverAddress.port, port);
}

QTEST_MAIN(TestPreferences)

#include "tst_preferences.moc"
