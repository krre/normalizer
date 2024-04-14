#include "ui/dialog/PreferencesDialog.h"
#include "tests/common/TestSettings.h"
#include <QTest>
#include <QLineEdit>

static constexpr auto NormHostUrl = "url";

class TestPreferences : public QObject {
    Q_OBJECT
private slots:
    void readSettings();
    void setSettings();
};

void TestPreferences::readSettings() {
    TestSettings::NormHost normHost;
    normHost.url = NormHostUrl;

    TestSettings settings;
    settings.setNormHost(normHost);

    PreferencesDialog preferencesDialog(&settings);
    auto urlLineEdit = static_cast<QLineEdit*>(preferencesDialog.focusWidget());

    QCOMPARE(urlLineEdit->text(), NormHostUrl);
}

void TestPreferences::setSettings() {
    TestSettings settings;

    PreferencesDialog preferencesDialog(&settings);
    static_cast<QLineEdit*>(preferencesDialog.focusWidget())->setText(NormHostUrl);
    preferencesDialog.accept();

    QCOMPARE(settings.normHost().url, NormHostUrl);
}

QTEST_MAIN(TestPreferences)

#include "TestPreferences.moc"
