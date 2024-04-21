#include "ui/dialog/PreferencesDialog.h"
#include "tests/common/TestSettings.h"
#include <QTest>
#include <QLineEdit>

static constexpr auto DevelopmentServerUrl = "url";

class TestPreferences : public QObject {
    Q_OBJECT
private slots:
    void readSettings();
    void setSettings();
};

void TestPreferences::readSettings() {
    TestSettings::DevelopmentServer developmentServer;
    developmentServer.url = DevelopmentServerUrl;

    TestSettings settings;
    settings.setDevelopmentServer(developmentServer);

    PreferencesDialog preferencesDialog(&settings);
    auto urlLineEdit = static_cast<QLineEdit*>(preferencesDialog.focusWidget());

    QCOMPARE(urlLineEdit->text(), DevelopmentServerUrl);
}

void TestPreferences::setSettings() {
    TestSettings settings;

    PreferencesDialog preferencesDialog(&settings);
    static_cast<QLineEdit*>(preferencesDialog.focusWidget())->setText(DevelopmentServerUrl);
    preferencesDialog.accept();

    QCOMPARE(settings.developmentServer().url, DevelopmentServerUrl);
}

QTEST_MAIN(TestPreferences)

#include "TestPreferences.moc"
