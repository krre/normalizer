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
    void createNewProject();
};

TestNewProject::TestNewProject() {

}

TestNewProject::~TestNewProject() {

}

void TestNewProject::createNewProject() {
    NewProject newProject("dir");

    QLineEdit* nameLineEdit = newProject.findChild<QLineEdit*>(ObjectName::Name);
    QLineEdit* directoryLineEdit = newProject.findChild<QLineEdit*>(ObjectName::Directory);
    QPushButton* okButton = newProject.findChild<QDialogButtonBox*>(ObjectName::ButtonBox)->button(QDialogButtonBox::Ok);

    QCOMPARE(newProject.name(), QString());
    QCOMPARE(newProject.directory(), "dir");
    QCOMPARE(okButton->isEnabled(), false);

    nameLineEdit->setText("");
    directoryLineEdit->setText("");
    QCOMPARE(okButton->isEnabled(), false);

    nameLineEdit->setText("name");
    directoryLineEdit->setText("");
    QCOMPARE(okButton->isEnabled(), false);

    directoryLineEdit->setText("name");
    directoryLineEdit->setText("dir");
    QCOMPARE(okButton->isEnabled(), true);
}

QTEST_MAIN(TestNewProject)

#include "tst_newproject.moc"
