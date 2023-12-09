#include "ui/dialog/account/RegisterAccountDialog.h"
#include "tests/common/TestAccount.h"
#include <QTest>
#include <QLineEdit>

constexpr auto Login = "admin";
constexpr auto FullName = "Morpheus";
constexpr auto Email = "admin@example.com";
constexpr auto Password = "qwerty";

class TestRegisterAccount : public QObject {
    Q_OBJECT
private slots:
    void validData();
};

void TestRegisterAccount::validData() {
    TestAccount account;
    RegisterAccountDialog registerAccountDialog(&account);

    auto loginLineEdit = static_cast<QLineEdit*>(registerAccountDialog.focusWidget());
    loginLineEdit->setText(Login);

    QTest::keyClick(&registerAccountDialog, Qt::Key_Tab);
    auto fullNameLineEdit = static_cast<QLineEdit*>(registerAccountDialog.focusWidget());
    fullNameLineEdit->setText(FullName);

    QTest::keyClick(&registerAccountDialog, Qt::Key_Tab);
    auto emailLineEdit = static_cast<QLineEdit*>(registerAccountDialog.focusWidget());
    emailLineEdit->setText(Email);

    QTest::keyClick(&registerAccountDialog, Qt::Key_Tab);
    auto passwordLineEdit = static_cast<QLineEdit*>(registerAccountDialog.focusWidget());
    passwordLineEdit->setText(Password);

    QTest::keyClick(&registerAccountDialog, Qt::Key_Tab);
    auto confirmPasswordLineEdit = static_cast<QLineEdit*>(registerAccountDialog.focusWidget());
    confirmPasswordLineEdit->setText(Password);

    registerAccountDialog.accept();

    QCOMPARE(account.m_createAccount.login, Login);
    QCOMPARE(account.m_createAccount.fullName, FullName);
    QCOMPARE(account.m_createAccount.email, Email);
    QCOMPARE(account.m_createAccount.password, Password);
}

QTEST_MAIN(TestRegisterAccount)

#include "tst_register_account.moc"
