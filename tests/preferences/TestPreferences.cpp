#include "TestSettings.h"
#include <ui/dialog/Preferences.h>
#include <settings/Settings.h>
#include <QTest>
#include <QLineEdit>
#include <QCheckBox>

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
    settings.setPathWorkspace(PathWorkspace);
    settings.setLoggingVulkan(LoggingVulkan);

    Preferences preferences(&settings);

    QTest::keyClick(&preferences, Qt::Key_Tab); // OK button
    QTest::keyClick(&preferences, Qt::Key_Tab); // Cancel button
    QTest::keyClick(&preferences, Qt::Key_Tab);
    auto workspaceLineEdit = static_cast<QLineEdit*>(preferences.focusWidget());

    QTest::keyClick(&preferences, Qt::Key_Tab); // Browse button
    QTest::keyClick(&preferences, Qt::Key_Tab);
    auto vulkanCheckBox = static_cast<QCheckBox*>(preferences.focusWidget());

    QCOMPARE(workspaceLineEdit->text(), PathWorkspace);
    QCOMPARE(vulkanCheckBox->isChecked(), LoggingVulkan);
}

void TestPreferences::setPreferences() {
    TestSettings settings;

    Preferences preferences(&settings);

    QTest::keyClick(&preferences, Qt::Key_Tab); // OK button
    QTest::keyClick(&preferences, Qt::Key_Tab); // Cancel button
    QTest::keyClick(&preferences, Qt::Key_Tab);
    auto workspaceLineEdit = static_cast<QLineEdit*>(preferences.focusWidget());
    workspaceLineEdit->setText(PathWorkspace);

    QTest::keyClick(&preferences, Qt::Key_Tab); // Browse button
    QTest::keyClick(&preferences, Qt::Key_Tab);
    auto vulkanCheckBox = static_cast<QCheckBox*>(preferences.focusWidget());
    vulkanCheckBox->setChecked(LoggingVulkan);

    preferences.accept();

    QCOMPARE(settings.pathWorkspace(), PathWorkspace);
}

QTEST_MAIN(TestPreferences)

#include "TestPreferences.moc"
