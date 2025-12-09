#include "TestSettings.h"
#include <ui/dialog/Preferences.h>
#include <settings/Settings.h>
#include <QTest>
#include <QLineEdit>
#include <QCheckBox>

constexpr auto UiLoadLastProject = true;
constexpr auto NetworkPort = 5555;
constexpr auto PathWorkspace = "NormWorkspace";
constexpr auto LoggingVulkan = true;

class TestPreferences : public QObject {
    Q_OBJECT
private slots:
    void readPreferences();
    void setPreferences();
};

void TestPreferences::readPreferences() {
    TestSettings settings;
    settings.setUiLoadLastProject(UiLoadLastProject);
    settings.setNetworkPort(NetworkPort);
    settings.setPathWorkspace(PathWorkspace);
    settings.setLoggingVulkan(LoggingVulkan);

    Preferences preferences(&settings);

    QTest::keyClick(&preferences, Qt::Key_Tab); // OK button
    QTest::keyClick(&preferences, Qt::Key_Tab); // Cancel button
    QTest::keyClick(&preferences, Qt::Key_Tab);
    auto loadLastProjectCheckBox = static_cast<QCheckBox*>(preferences.focusWidget());

    QTest::keyClick(&preferences, Qt::Key_Tab);
    auto portLineEdit = static_cast<QLineEdit*>(preferences.focusWidget());

    QTest::keyClick(&preferences, Qt::Key_Tab);
    auto workspaceLineEdit = static_cast<QLineEdit*>(preferences.focusWidget());

    QTest::keyClick(&preferences, Qt::Key_Tab); // Browse button
    QTest::keyClick(&preferences, Qt::Key_Tab);
    auto vulkanCheckBox = static_cast<QCheckBox*>(preferences.focusWidget());

    QCOMPARE(loadLastProjectCheckBox->isChecked(), UiLoadLastProject);
    QCOMPARE(portLineEdit->text().toInt(), NetworkPort);
    QCOMPARE(workspaceLineEdit->text(), PathWorkspace);
    QCOMPARE(vulkanCheckBox->isChecked(), LoggingVulkan);
}

void TestPreferences::setPreferences() {
    TestSettings settings;

    Preferences preferences(&settings);

    QTest::keyClick(&preferences, Qt::Key_Tab); // OK button
    QTest::keyClick(&preferences, Qt::Key_Tab); // Cancel button
    QTest::keyClick(&preferences, Qt::Key_Tab);
    auto loadLastProjectCheckBox = static_cast<QCheckBox*>(preferences.focusWidget());
    loadLastProjectCheckBox->setChecked(UiLoadLastProject);

    QTest::keyClick(&preferences, Qt::Key_Tab);
    auto portLineEdit = static_cast<QLineEdit*>(preferences.focusWidget());
    portLineEdit->setText(QString::number(NetworkPort));

    QTest::keyClick(&preferences, Qt::Key_Tab);
    auto workspaceLineEdit = static_cast<QLineEdit*>(preferences.focusWidget());
    workspaceLineEdit->setText(PathWorkspace);

    QTest::keyClick(&preferences, Qt::Key_Tab); // Browse button
    QTest::keyClick(&preferences, Qt::Key_Tab);
    auto vulkanCheckBox = static_cast<QCheckBox*>(preferences.focusWidget());
    vulkanCheckBox->setChecked(LoggingVulkan);

    preferences.accept();

    QCOMPARE(settings.networkPort(), NetworkPort);
    QCOMPARE(settings.pathWorkspace(), PathWorkspace);
}

QTEST_MAIN(TestPreferences)

#include "TestPreferences.moc"
