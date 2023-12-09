#include "ui/dialog/account/ChangePasswordDialog.h"
#include "tests/common/TestAccount.h"
#include <QTest>
#include <QLineEdit>

constexpr auto OldPassword = "123456";
constexpr auto NewPassword = "654321";

class TestChangePassword : public QObject {
    Q_OBJECT
private slots:
    void validData();
};

void TestChangePassword::validData() {
    TestAccount account;
    ChangePasswordDialog changePasswordDialog(&account);

    auto oldPasswordLineEdit = static_cast<QLineEdit*>(changePasswordDialog.focusWidget());
    oldPasswordLineEdit->setText(OldPassword);

    QTest::keyClick(&changePasswordDialog, Qt::Key_Tab);
    auto newPasswordLineEdit = static_cast<QLineEdit*>(changePasswordDialog.focusWidget());
    newPasswordLineEdit->setText(NewPassword);

    QTest::keyClick(&changePasswordDialog, Qt::Key_Tab);
    auto confirmPasswordLineEdit = static_cast<QLineEdit*>(changePasswordDialog.focusWidget());
    confirmPasswordLineEdit->setText(NewPassword);

    changePasswordDialog.accept();

    QCOMPARE(account.m_password.oldPassword, OldPassword);
    QCOMPARE(account.m_password.newPassword, NewPassword);
}

QTEST_MAIN(TestChangePassword)

#include "tst_change_password.moc"
