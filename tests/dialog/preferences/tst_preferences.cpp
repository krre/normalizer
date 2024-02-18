#include "ui/dialog/PreferencesDialog.h"
#include "external/settings/Settings.h"
#include <QTest>
#include <QLineEdit>

static constexpr auto LocalDirectory = "directory";
static constexpr auto RemoteHost = "host";

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

    void setProject(const Project& project) override {
        m_project = project;
    }

    Project project() const override {
        return m_project;
    }

    void setProjectLocation(const ProjectLocation& projectLocation) override {
        m_projectLocation = projectLocation;
    }

    ProjectLocation projectLocation() const override {
        return m_projectLocation;
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
    Project m_project;
    ProjectLocation m_projectLocation;
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
    Settings::ProjectLocation projectLocation;
    projectLocation.directory = LocalDirectory;
    projectLocation.host = RemoteHost;

    TestSettings settings;
    settings.m_projectLocation = projectLocation;

    PreferencesDialog preferencesDialog(&settings);
    auto directoryLineEdit = static_cast<QLineEdit*>(preferencesDialog.focusWidget());

    QTest::keyClick(&preferencesDialog, Qt::Key_Tab);
    QTest::keyClick(&preferencesDialog, Qt::Key_Tab);
    auto hostLineEdit = static_cast<QLineEdit*>(preferencesDialog.focusWidget());

    QCOMPARE(directoryLineEdit->text(), LocalDirectory);
    QCOMPARE(hostLineEdit->text(), RemoteHost);
}

void TestPreferences::setSettings() {
    TestSettings settings;

    PreferencesDialog preferencesDialog(&settings);

    auto directoryLineEdit = static_cast<QLineEdit*>(preferencesDialog.focusWidget());
    directoryLineEdit->setText(LocalDirectory);

    QTest::keyClick(&preferencesDialog, Qt::Key_Tab);
    QTest::keyClick(&preferencesDialog, Qt::Key_Tab);

    auto hostLineEdit = static_cast<QLineEdit*>(preferencesDialog.focusWidget());
    hostLineEdit->setText(RemoteHost);

    preferencesDialog.accept();

    QCOMPARE(settings.m_projectLocation.directory, LocalDirectory);
    QCOMPARE(settings.m_projectLocation.host, RemoteHost);
}

QTEST_MAIN(TestPreferences)

#include "tst_preferences.moc"
