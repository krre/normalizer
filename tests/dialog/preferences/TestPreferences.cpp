#include "ui/dialog/PreferencesDialog.h"
#include "tests/common/TestSettings.h"
#include <QTest>
#include <QLineEdit>

static constexpr auto LocalWorkspace = "workspace";
static constexpr auto RemoteHost = "host";

static constexpr auto NormLocationType = Settings::NormLocation::Type::Custom;
static constexpr auto NormLocationDirectory = "directory";

class TestPreferences : public QObject {
    Q_OBJECT
private slots:
    void readSettings();
    void setSettings();
};

void TestPreferences::readSettings() {
    TestSettings::ProjectLocation projectLocation;
    projectLocation.workspace = LocalWorkspace;
    projectLocation.host = RemoteHost;

    TestSettings::NormLocation normLocation;
    normLocation.type = NormLocationType;
    normLocation.directory = NormLocationDirectory;

    TestSettings settings;
    settings.setProjectLocation(projectLocation);
    settings.setNormLocation(normLocation);

    PreferencesDialog preferencesDialog(&settings);
    auto workspaceDirectoryLineEdit = static_cast<QLineEdit*>(preferencesDialog.focusWidget());

    QTest::keyClick(&preferencesDialog, Qt::Key_Tab);
    QTest::keyClick(&preferencesDialog, Qt::Key_Tab);
    auto hostLineEdit = static_cast<QLineEdit*>(preferencesDialog.focusWidget());

    QTest::keyClick(&preferencesDialog, Qt::Key_Tab);
    QTest::keyClick(&preferencesDialog, Qt::Key_Tab);
    QTest::keyClick(&preferencesDialog, Qt::Key_Tab);
    auto normDirectoryLineEdit = static_cast<QLineEdit*>(preferencesDialog.focusWidget());

    QCOMPARE(workspaceDirectoryLineEdit->text(), LocalWorkspace);
    QCOMPARE(hostLineEdit->text(), RemoteHost);
    QCOMPARE(normDirectoryLineEdit->text(), NormLocationDirectory);
}

void TestPreferences::setSettings() {
    TestSettings settings;

    PreferencesDialog preferencesDialog(&settings);

    static_cast<QLineEdit*>(preferencesDialog.focusWidget())->setText(LocalWorkspace);

    QTest::keyClick(&preferencesDialog, Qt::Key_Tab);
    QTest::keyClick(&preferencesDialog, Qt::Key_Tab);
    static_cast<QLineEdit*>(preferencesDialog.focusWidget())->setText(RemoteHost);

    QTest::keyClick(&preferencesDialog, Qt::Key_Tab);
    QTest::keyClick(&preferencesDialog, Qt::Key_Down);
    QTest::keyClick(&preferencesDialog, Qt::Key_Tab);
    QTest::keyClick(&preferencesDialog, Qt::Key_Tab);
    static_cast<QLineEdit*>(preferencesDialog.focusWidget())->setText(NormLocationDirectory);

    preferencesDialog.accept();

    QCOMPARE(settings.projectLocation().workspace, LocalWorkspace);
    QCOMPARE(settings.projectLocation().host, RemoteHost);
    QCOMPARE(settings.normLocation().type, NormLocationType);
    QCOMPARE(settings.normLocation().directory, NormLocationDirectory);
}

QTEST_MAIN(TestPreferences)

#include "TestPreferences.moc"
