#include "ui/dialog/account/ProfileDialog.h"
#include "tests/common/TestNetworkManager.h"
#include <QTest>
#include <QLineEdit>

constexpr auto Login = "admin";
constexpr auto Email = "admin@example.com";
constexpr auto FullName = "Admin";

class TestProfile : public QObject {
    Q_OBJECT
private slots:
    void getData();
    void updateData();
};

void TestProfile::getData() {
    TestNetworkManager networkManager;
    networkManager.m_user.login = Login;
    networkManager.m_user.email = Email;
    networkManager.m_user.fullName = FullName;

    ProfileDialog profileDialog(&networkManager);

    QLineEdit* fullNameLineEdit = static_cast<QLineEdit*>(profileDialog.focusWidget());

    QTest::keyClick(&profileDialog, Qt::Key_Backtab);

    QLineEdit* emailLineEdit = static_cast<QLineEdit*>(profileDialog.focusWidget());

    QTest::keyClick(&profileDialog, Qt::Key_Backtab);

    QLineEdit* loginLineEdit = static_cast<QLineEdit*>(profileDialog.focusWidget());

    profileDialog.accept();

    QCOMPARE(networkManager.m_user.fullName, fullNameLineEdit->text());
    QCOMPARE(networkManager.m_user.email, emailLineEdit->text());
    QCOMPARE(networkManager.m_user.login, loginLineEdit->text());
}

void TestProfile::updateData() {
    TestNetworkManager networkManager;
    ProfileDialog profileDialog(&networkManager);

    QLineEdit* fullNameLineEdit = static_cast<QLineEdit*>(profileDialog.focusWidget());
    fullNameLineEdit->setText(FullName);

    QTest::keyClick(&profileDialog, Qt::Key_Tab);

    profileDialog.accept();

    QCOMPARE(networkManager.m_user.fullName, FullName);
}

QTEST_MAIN(TestProfile)

#include "tst_profile.moc"
