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
    NewProject newProject;
    QPushButton* okButton = newProject.findChild<QDialogButtonBox*>(ObjectName::ButtonBox)->button(QDialogButtonBox::Ok);

    QCOMPARE(newProject.name(), QString());
    QCOMPARE(okButton->isEnabled(), false);
}

void TestNewProject::setFields() {
    NewProject newProject;

    QLineEdit* nameLineEdit = newProject.findChild<QLineEdit*>(ObjectName::Name);
    QPushButton* okButton = newProject.findChild<QDialogButtonBox*>(ObjectName::ButtonBox)->button(QDialogButtonBox::Ok);

    QFETCH(QString, name);
    QFETCH(bool, okEnabled);

    nameLineEdit->setText(name);

    QCOMPARE(okButton->isEnabled(), okEnabled);
}

void TestNewProject::setFields_data() {
    QTest::addColumn<QString>("name");
    QTest::addColumn<bool>("okEnabled");

    QTest::newRow("all-empty") << "" << false;
    QTest::newRow("only-name") << "name" << false;
    QTest::newRow("all-filled") << "name" << true;
}

QTEST_MAIN(TestNewProject)

#include "tst_newproject.moc"
