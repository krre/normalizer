#include "TestSettings.h"
#include <ui/dialog/Preferences.h>
#include <settings/Settings.h>
#include <QTest>
#include <QLineEdit>

constexpr auto Workspace = "NormWorkspace";

class TestPreferences : public QObject {
    Q_OBJECT
private slots:
    void readPreferences();
    void setPreferences();
};

void TestPreferences::readPreferences() {
    TestSettings settings;
    settings.setPathWorkspace(Workspace);

    Preferences preferences(&settings);

    QTest::keyClick(&preferences, Qt::Key_Tab); // OK button
    QTest::keyClick(&preferences, Qt::Key_Tab); // Cancel button
    QTest::keyClick(&preferences, Qt::Key_Tab);
    auto workspaceLineEdit = static_cast<QLineEdit*>(preferences.focusWidget());

    QCOMPARE(workspaceLineEdit->text(), Workspace);
}

void TestPreferences::setPreferences() {
    TestSettings settings;

    Preferences preferences(&settings);

    QTest::keyClick(&preferences, Qt::Key_Tab); // OK button
    QTest::keyClick(&preferences, Qt::Key_Tab); // Cancel button
    QTest::keyClick(&preferences, Qt::Key_Tab);
    auto workspaceLineEdit = static_cast<QLineEdit*>(preferences.focusWidget());
    workspaceLineEdit->setText(Workspace);

    preferences.accept();

    QCOMPARE(settings.pathWorkspace(), Workspace);
}

QTEST_MAIN(TestPreferences)

#include "TestPreferences.moc"
