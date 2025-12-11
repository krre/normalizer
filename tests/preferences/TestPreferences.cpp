#include "TestSettings.h"
#include <ui/dialog/Preferences.h>
#include <settings/Settings.h>
#include <QTest>
#include <QLineEdit>
#include <QCheckBox>
#include <QSpinBox>

constexpr auto UiLoadLastProject = true;
constexpr auto NetworkHost = "ws://127.0.0.1";
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
    settings.setNetworkHost(NetworkHost);
    settings.setNetworkPort(NetworkPort);
    settings.setPathWorkspace(PathWorkspace);
    settings.setLoggingVulkan(LoggingVulkan);

    Preferences preferences(&settings);

    QTest::keyClick(&preferences, Qt::Key_Tab); // OK button
    QTest::keyClick(&preferences, Qt::Key_Tab); // Cancel button
    QTest::keyClick(&preferences, Qt::Key_Tab);
    auto loadLastProjectCheckBox = static_cast<QCheckBox*>(preferences.focusWidget());

    QTest::keyClick(&preferences, Qt::Key_Tab);
    auto hostLineEdit = static_cast<QLineEdit*>(preferences.focusWidget());

    QTest::keyClick(&preferences, Qt::Key_Tab);
    auto portLineEdit = static_cast<QSpinBox*>(preferences.focusWidget());

    QTest::keyClick(&preferences, Qt::Key_Tab);
    auto workspaceLineEdit = static_cast<QLineEdit*>(preferences.focusWidget());

    QTest::keyClick(&preferences, Qt::Key_Tab); // Browse button
    QTest::keyClick(&preferences, Qt::Key_Tab);
    auto vulkanCheckBox = static_cast<QCheckBox*>(preferences.focusWidget());

    QCOMPARE(loadLastProjectCheckBox->isChecked(), UiLoadLastProject);
    QCOMPARE(hostLineEdit->text(), NetworkHost);
    QCOMPARE(portLineEdit->value(), NetworkPort);
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
    auto hostLineEdit = static_cast<QLineEdit*>(preferences.focusWidget());
    hostLineEdit->setText(NetworkHost);

    QTest::keyClick(&preferences, Qt::Key_Tab);
    auto portLineEdit = static_cast<QSpinBox*>(preferences.focusWidget());
    portLineEdit->setValue(NetworkPort);

    QTest::keyClick(&preferences, Qt::Key_Tab);
    auto workspaceLineEdit = static_cast<QLineEdit*>(preferences.focusWidget());
    workspaceLineEdit->setText(PathWorkspace);

    QTest::keyClick(&preferences, Qt::Key_Tab); // Browse button
    QTest::keyClick(&preferences, Qt::Key_Tab);
    auto vulkanCheckBox = static_cast<QCheckBox*>(preferences.focusWidget());
    vulkanCheckBox->setChecked(LoggingVulkan);

    preferences.accept();

    QCOMPARE(settings.uiLoadLastProject(), UiLoadLastProject);
    QCOMPARE(settings.networkHost(), NetworkHost);
    QCOMPARE(settings.networkPort(), NetworkPort);
    QCOMPARE(settings.pathWorkspace(), PathWorkspace);
    QCOMPARE(settings.loggingVulkan(), LoggingVulkan);
}

QTEST_MAIN(TestPreferences)

#include "TestPreferences.moc"
