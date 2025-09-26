#include <ui/dialog/NewProject.h>
#include <project/Project.h>
#include <QTest>
#include <QLineEdit>
#include <QComboBox>

constexpr auto WorkDir = "/home/user/norm";
constexpr auto Name = "test";
constexpr auto Directory = "/home/user/git";
constexpr auto Target = Project::Target::Library;

class TestNewProject : public QObject {
    Q_OBJECT
private slots:
    void readProject();
};

void TestNewProject::readProject() {
    NewProject newProject(WorkDir);

    QCOMPARE(newProject.directory(), WorkDir);

    auto nameLineEdit = static_cast<QLineEdit*>(newProject.focusWidget());
    nameLineEdit->setText(Name);

    QCOMPARE(newProject.name(), Name);

    QTest::keyClick(&newProject, Qt::Key_Tab);

    auto directoryLineEdit = static_cast<QLineEdit*>(newProject.focusWidget());
    directoryLineEdit->setText(Directory);

    QCOMPARE(newProject.directory(), Directory);

    QTest::keyClick(&newProject, Qt::Key_Tab); // Browse button
    QTest::keyClick(&newProject, Qt::Key_Tab); // Target combobox
    auto targetComboBox = static_cast<QComboBox*>(newProject.focusWidget());
    targetComboBox->setCurrentIndex(int(Project::Target::Library));

    QCOMPARE(newProject.target(), Target);
}

QTEST_MAIN(TestNewProject)

#include "TestNewProject.moc"
