#include "ui/dialog/project/NewProjectDialog.h"
#include "tests/common/TestProcess.h"
#include "tests/common/TestSettings.h"
#include <QTest>
#include <QLineEdit>
#include <QComboBox>

static constexpr auto NormDirectory = "norm";
static constexpr auto NormLocationType = TestSettings::NormLocation::Type::Custom;

static constexpr auto ProjectName = "name";
static constexpr auto ProjectDirectory = "directory";
static constexpr auto ProjectTarget = Project::Target::Library;

class TestNewProject : public QObject {
    Q_OBJECT
private slots:
    void createProject();
};

void TestNewProject::createProject() {
    TestProcess process;

    TestSettings::NormLocation normLocation;
    normLocation.directory = NormDirectory;
    normLocation.type = NormLocationType;

    TestSettings settings;
    settings.setNormLocation(normLocation);

    NewProjectDialog newProjectDialog(&process, &settings);

    static_cast<QLineEdit*>(newProjectDialog.focusWidget())->setText(ProjectName);

    QTest::keyClick(&newProjectDialog, Qt::Key_Tab);
    static_cast<QLineEdit*>(newProjectDialog.focusWidget())->setText(ProjectDirectory);

    QTest::keyClick(&newProjectDialog, Qt::Key_Tab);
    qDebug() << newProjectDialog.focusWidget();

    QTest::keyClick(&newProjectDialog, Qt::Key_Tab);
    static_cast<QComboBox*>(newProjectDialog.focusWidget())->setCurrentIndex(int(Project::Target::Library));

    newProjectDialog.accept();

    QCOMPARE(process.m_projectName, ProjectName);
    QCOMPARE(process.m_projectDirectory, ProjectDirectory);
    QCOMPARE(process.m_projectTarget, ProjectTarget);
}

QTEST_MAIN(TestNewProject)

#include "TestNewProject.moc"
