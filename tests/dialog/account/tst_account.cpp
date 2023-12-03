#include "ui/dialog/account/AccountDialog.h"
#include "tests/common/TestNetworkManager.h"
#include <QTest>
#include <QLineEdit>

constexpr auto Login = "admin";
constexpr auto Email = "admin@example.com";
constexpr auto FullName = "Admin";

class TestAccount : public QObject {
    Q_OBJECT
private slots:
    void getData();
    void updateData();
};

void TestAccount::getData() {
    TestNetworkManager networkManager;
    networkManager.m_user.login = Login;
    networkManager.m_user.email = Email;
    networkManager.m_user.fullName = FullName;

    AccountDialog AccountDialog(&networkManager);

    QLineEdit* fullNameLineEdit = static_cast<QLineEdit*>(AccountDialog.focusWidget());

    QTest::keyClick(&AccountDialog, Qt::Key_Backtab);

    QLineEdit* emailLineEdit = static_cast<QLineEdit*>(AccountDialog.focusWidget());

    QTest::keyClick(&AccountDialog, Qt::Key_Backtab);

    QLineEdit* loginLineEdit = static_cast<QLineEdit*>(AccountDialog.focusWidget());

    AccountDialog.accept();

    QCOMPARE(networkManager.m_user.fullName, fullNameLineEdit->text());
    QCOMPARE(networkManager.m_user.email, emailLineEdit->text());
    QCOMPARE(networkManager.m_user.login, loginLineEdit->text());
}

void TestAccount::updateData() {
    TestNetworkManager networkManager;
    AccountDialog accountDialog(&networkManager);

    QLineEdit* fullNameLineEdit = static_cast<QLineEdit*>(accountDialog.focusWidget());
    fullNameLineEdit->setText(FullName);

    QTest::keyClick(&accountDialog, Qt::Key_Tab);

    accountDialog.accept();

    QCOMPARE(networkManager.m_user.fullName, FullName);
}

QTEST_MAIN(TestAccount)

#include "tst_account.moc"
