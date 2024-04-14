#include "ui/dialog/project/NewProjectDialog.h"
#include "program/Project.h"
#include "tests/common/TestSettings.h"
#include <QTest>
#include <QLineEdit>
#include <QComboBox>

static constexpr auto ProjectName = "name";
static constexpr auto ProjectTarget = Project::Target::Library;

class TestNewProject : public QObject {
    Q_OBJECT
private slots:
    void createProject();
};

void TestNewProject::createProject() {
    TestSettings settings;

    NewProjectDialog newProjectDialog(&settings);

    static_cast<QLineEdit*>(newProjectDialog.focusWidget())->setText(ProjectName);

    QTest::keyClick(&newProjectDialog, Qt::Key_Tab);
    static_cast<QComboBox*>(newProjectDialog.focusWidget())->setCurrentIndex(int(Project::Target::Library));

    newProjectDialog.accept();
}

QTEST_MAIN(TestNewProject)

#include "TestNewProject.moc"
