#include "ui/dialog/account/LoginDialog.h"
#include "tests/common/TestNetworkManager.h"
#include <QTest>
#include <QLineEdit>

constexpr auto Email = "admin@example.com";
constexpr auto Password = "qwerty";

class TestLogin : public QObject {
    Q_OBJECT
private slots:
    void validData();
};

void TestLogin::validData() {
    TestNetworkManager networkManager;
    LoginDialog loginDialog(&networkManager);

    QLineEdit* emailLineEdit = static_cast<QLineEdit*>(loginDialog.focusWidget());
    emailLineEdit->setText(Email);

    QTest::keyClick(&loginDialog, Qt::Key_Tab);

    QLineEdit* passwordLineEdit = static_cast<QLineEdit*>(loginDialog.focusWidget());
    passwordLineEdit->setText(Password);

    loginDialog.accept();

    QCOMPARE(networkManager.m_user.email, Email);
    QCOMPARE(networkManager.m_user.password, Password);
}

QTEST_MAIN(TestLogin)

#include "tst_login.moc"
