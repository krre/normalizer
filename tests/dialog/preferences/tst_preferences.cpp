#include "ui/dialog/PreferencesDialog.h"
#include "external/settings/Settings.h"
#include <QTest>
#include <QLineEdit>

static constexpr auto LocalWorkspace = "workspace";
static constexpr auto RemoteHost = "host";

static constexpr auto NormLocationType = Settings::NormLocation::Type::Custom;
static constexpr auto NormLocationDirectory = "directory";

class TestSettings : public Settings {
public:
    void setMainWindow(const MainWindow& mainWindow [[maybe_unused]]) override {}

    Settings::MainWindow mainWindow() const override {
        return MainWindow();
    }

    void setAccount(const Account& account) override {
        m_account = account;
    }

    Account account() const override {
        return m_account;
    }

    void setProjectLocation(const ProjectLocation& projectLocation) override {
        m_projectLocation = projectLocation;
    }

    ProjectLocation projectLocation() const override {
        return m_projectLocation;
    }

    void setNormLocation(const NormLocation& normLocation) override {
        m_normLocation = normLocation;
    }

    NormLocation normLocation() const override {
        return m_normLocation;
    }

    void setProjectTable(const ProjectTable& projectTable) override {
        m_projectTable = projectTable;
    }

    ProjectTable projectTable() const override {
        return m_projectTable;
    }

    void setEditor(const Editor& editor) override {
        m_editor = editor;
    }

    Editor editor() const override {
        return m_editor;
    }

    Account m_account;
    ProjectLocation m_projectLocation;
    NormLocation m_normLocation;
    ProjectTable m_projectTable;
    Editor m_editor;
};

class TestPreferences : public QObject {
    Q_OBJECT
private slots:
    void readSettings();
    void setSettings();
};

void TestPreferences::readSettings() {
    TestSettings settings;
    settings.m_projectLocation.workspace = LocalWorkspace;
    settings.m_projectLocation.host = RemoteHost;

    settings.m_normLocation.type = NormLocationType;
    settings.m_normLocation.directory = NormLocationDirectory;

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

    QCOMPARE(settings.m_projectLocation.workspace, LocalWorkspace);
    QCOMPARE(settings.m_projectLocation.host, RemoteHost);
    QCOMPARE(settings.m_normLocation.type, NormLocationType);
    QCOMPARE(settings.m_normLocation.directory, NormLocationDirectory);
}

QTEST_MAIN(TestPreferences)

#include "tst_preferences.moc"
