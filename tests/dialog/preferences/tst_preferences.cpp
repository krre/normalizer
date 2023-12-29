#include "ui/dialog/PreferencesDialog.h"
#include "settings/Settings.h"
#include <QTest>
#include <QLineEdit>

static const QUrl ApiUrl = QUrl("localhost/api");
static const QUrl EditorUrl = QUrl("localhost/editor");

class TestSettings : public Settings {
public:
    void setMainWindow(const MainWindow& mainWindow [[maybe_unused]]) override {}

    Settings::MainWindow mainWindow() const override {
        return MainWindow();
    }

    bool containsGeometry() const override {
        return true;
    }

    void setServer(const Server& server) override {
        m_server = server;
    }

    Server server() const override {
        return m_server;
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

    Server m_server;
    Account m_account;
    Project m_project;
};

class TestPreferences : public QObject {
    Q_OBJECT
private slots:
    void readSettings();
    void setSettings();
};

void TestPreferences::readSettings() {
    Settings::Server server;
    server.api = ApiUrl.toString();
    server.editor = EditorUrl.toString();

    TestSettings settings;
    settings.m_server = server;

    PreferencesDialog preferencesDialog(&settings);

    auto apiUrlLineEdit = static_cast<QLineEdit*>(preferencesDialog.focusWidget());

    QTest::keyClick(&preferencesDialog, Qt::Key_Tab);
    auto editorUrlLineEdit = static_cast<QLineEdit*>(preferencesDialog.focusWidget());

    QCOMPARE(apiUrlLineEdit->text(), ApiUrl.toString());
    QCOMPARE(editorUrlLineEdit->text(), EditorUrl.toString());
}

void TestPreferences::setSettings() {
    TestSettings settings;

    PreferencesDialog preferencesDialog(&settings);

    auto apiUrlLineEdit = static_cast<QLineEdit*>(preferencesDialog.focusWidget());
    apiUrlLineEdit->setText(ApiUrl.toString());

    QTest::keyClick(&preferencesDialog, Qt::Key_Tab);
    auto editorUrlLineEdit = static_cast<QLineEdit*>(preferencesDialog.focusWidget());
    editorUrlLineEdit->setText(EditorUrl.toString());

    preferencesDialog.accept();

    QCOMPARE(settings.m_server.api, ApiUrl);
    QCOMPARE(settings.m_server.editor, EditorUrl);
}

QTEST_MAIN(TestPreferences)

#include "tst_preferences.moc"
