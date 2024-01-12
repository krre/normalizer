#include "ui/dialog/account/ChangePasswordDialog.h"
#include "external/network/controller/account/Account.h"
#include "external/network/RestApi.h"
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
    Async::Task<QVariant> get(const QString& endpoint [[maybe_unused]], const QUrlQuery& query = QUrlQuery()) override { co_return QVariant(); }
    Async::Task<QVariant> del(const QString& endpoint [[maybe_unused]]) override { co_return QVariant(); }
    Async::Task<QVariant> post(const QString& endpoint [[maybe_unused]], const QVariant& data = QVariant()) override { co_return QVariant(); }
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

    auto oldPasswordLineEdit = static_cast<QLineEdit*>(changePasswordDialog.focusWidget());
    oldPasswordLineEdit->setText(OldPassword);

    QTest::keyClick(&changePasswordDialog, Qt::Key_Tab);
    auto newPasswordLineEdit = static_cast<QLineEdit*>(changePasswordDialog.focusWidget());
    newPasswordLineEdit->setText(NewPassword);

    QTest::keyClick(&changePasswordDialog, Qt::Key_Tab);
    auto confirmPasswordLineEdit = static_cast<QLineEdit*>(changePasswordDialog.focusWidget());
    confirmPasswordLineEdit->setText(NewPassword);

    changePasswordDialog.accept();

    QCOMPARE(restApi.oldPassword, Utils::sha256(OldPassword));
    QCOMPARE(restApi.newPassword, Utils::sha256(NewPassword));
}

QTEST_MAIN(TestChangePassword)

#include "tst_change_password.moc"
