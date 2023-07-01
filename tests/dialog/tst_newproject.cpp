#include <QTest>

class TestNewProject : public QObject {
    Q_OBJECT
public:
    TestNewProject();
    ~TestNewProject();

private slots:
    void test();
};

TestNewProject::TestNewProject() {

}

TestNewProject::~TestNewProject() {

}

void TestNewProject::test() {

}

QTEST_MAIN(TestNewProject)

#include "tst_newproject.moc"
