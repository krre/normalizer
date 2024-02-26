#include "ui/dialog/account/ChangePasswordDialog.h"
#include "external/repository/network/controller/account/Account.h"
#include "external/repository/network/RestApi.h"
#include "core/Utils.h"
#include <QTest>
#include <QLineEdit>

constexpr auto OldPassword = "123456";
constexpr auto NewPassword = "654321";

class TestChangePassword : public QObject {
    Q_OBJECT
private slots:
    void validData();
};

class TestRestApi : public RestApi {
public:
    Async::Task<QVariant> put(const QString& endpoint [[maybe_unused]], const QVariant& data = QVariant()) override {
        oldPassword = data.toMap()["old_password"].toString();
        newPassword = data.toMap()["new_password"].toString();
        co_return QVariant();
    }

    QString oldPassword;
    QString newPassword;
};

void TestChangePassword::validData() {
    TestRestApi restApi;
    Controller::Account account(&restApi);
    ChangePasswordDialog changePasswordDialog(&account);

    static_cast<QLineEdit*>(changePasswordDialog.focusWidget())->setText(OldPassword);

    QTest::keyClick(&changePasswordDialog, Qt::Key_Tab);
    static_cast<QLineEdit*>(changePasswordDialog.focusWidget())->setText(NewPassword);

    QTest::keyClick(&changePasswordDialog, Qt::Key_Tab);
    static_cast<QLineEdit*>(changePasswordDialog.focusWidget())->setText(NewPassword);

    changePasswordDialog.accept();

    QCOMPARE(restApi.oldPassword, Utils::sha256(OldPassword));
    QCOMPARE(restApi.newPassword, Utils::sha256(NewPassword));
}

QTEST_MAIN(TestChangePassword)

#include "tst_change_password.moc"
