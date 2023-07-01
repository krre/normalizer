#include "ui/dialog/NewProject.h"
#include "core/ObjectNames.h"
#include <QTest>
#include <QTimer>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QLineEdit>

class TestNewProject : public QObject {
    Q_OBJECT
public:
    TestNewProject();
    ~TestNewProject();

private slots:
    void createDefault();
    void setFields();
    void setFields_data();
};

TestNewProject::TestNewProject() {

}

TestNewProject::~TestNewProject() {

}

void TestNewProject::createDefault() {
    constexpr auto dir = "dir";
    NewProject newProject(dir);
    QPushButton* okButton = newProject.findChild<QDialogButtonBox*>(ObjectName::ButtonBox)->button(QDialogButtonBox::Ok);

    QCOMPARE(newProject.name(), QString());
    QCOMPARE(newProject.directory(), dir);
    QCOMPARE(okButton->isEnabled(), false);
}

void TestNewProject::setFields() {
    NewProject newProject("");

    QLineEdit* nameLineEdit = newProject.findChild<QLineEdit*>(ObjectName::Name);
    QLineEdit* directoryLineEdit = newProject.findChild<QLineEdit*>(ObjectName::Directory);
    QPushButton* okButton = newProject.findChild<QDialogButtonBox*>(ObjectName::ButtonBox)->button(QDialogButtonBox::Ok);

    QFETCH(QString, name);
    QFETCH(QString, directory);
    QFETCH(bool, okEnabled);

    nameLineEdit->setText(name);
    directoryLineEdit->setText(directory);

    QCOMPARE(okButton->isEnabled(), okEnabled);
}

void TestNewProject::setFields_data() {
    QTest::addColumn<QString>("name");
    QTest::addColumn<QString>("directory");
    QTest::addColumn<bool>("okEnabled");

    QTest::newRow("all-empty") << "" << "" << false;
    QTest::newRow("only-name") << "name" << "" << false;
    QTest::newRow("only-dir") << "" << "dir" << false;
    QTest::newRow("all-filled") << "name" << "dir" << true;
}

QTEST_MAIN(TestNewProject)

#include "tst_newproject.moc"
