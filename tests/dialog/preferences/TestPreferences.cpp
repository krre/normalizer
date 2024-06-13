#include "ui/dialog/PreferencesDialog.h"
#include "tests/common/TestSettings.h"
#include <QTest>
#include <QLineEdit>
#include <QComboBox>

static constexpr auto DevelopmentServerUrl = "url";
static constexpr int GraphicsAdapter = 1;
const QStringList Adapters = { "adapter1", "adapter2" };

class TestPreferences : public QObject {
    Q_OBJECT
private slots:
    void readSettings();
    void setSettings();
};

void TestPreferences::readSettings() {
    TestSettings::DevelopmentServer developmentServer;
    developmentServer.url = DevelopmentServerUrl;

    TestSettings::Graphics graphics;
    graphics.adapter = GraphicsAdapter;

    TestSettings settings;
    settings.setDevelopmentServer(developmentServer);
    settings.setGraphics(graphics);

    PreferencesDialog preferencesDialog(Adapters, &settings);

    auto urlLineEdit = static_cast<QLineEdit*>(preferencesDialog.focusWidget());

    QTest::keyClick(&preferencesDialog, Qt::Key_Tab);
    auto adapterComboBox = static_cast<QComboBox*>(preferencesDialog.focusWidget());

    QCOMPARE(urlLineEdit->text(), DevelopmentServerUrl);
    QCOMPARE(adapterComboBox->currentIndex(), GraphicsAdapter);
}

void TestPreferences::setSettings() {
    TestSettings settings;

    PreferencesDialog preferencesDialog(Adapters, &settings);

    static_cast<QLineEdit*>(preferencesDialog.focusWidget())->setText(DevelopmentServerUrl);

    QTest::keyClick(&preferencesDialog, Qt::Key_Tab);
    static_cast<QComboBox*>(preferencesDialog.focusWidget())->setCurrentIndex(GraphicsAdapter);

    preferencesDialog.accept();

    QCOMPARE(settings.developmentServer().url, DevelopmentServerUrl);
    QCOMPARE(settings.graphics().adapter, GraphicsAdapter);
}

QTEST_MAIN(TestPreferences)

#include "TestPreferences.moc"
