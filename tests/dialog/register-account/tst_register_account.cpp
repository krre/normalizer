#include "ui/dialog/account/SignUpDialog.h"
#include "external/repository/network/controller/account/Account.h"
#include "external/repository/network/RestApi.h"
#include "core/Utils.h"
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

class TestRestApi : public RestApi {
public:
    Async::Task<QVariant> get(const QString& endpoint [[maybe_unused]], const QUrlQuery& query = QUrlQuery()) override { co_return QVariant(); }
    Async::Task<QVariant> del(const QString& endpoint [[maybe_unused]]) override { co_return QVariant(); }
    Async::Task<QVariant> post(const QString& endpoint [[maybe_unused]], const QVariant& data = QVariant()) override {
        login = data.toMap()["login"].toString();
        fullName = data.toMap()["full_name"].toString();
        email = data.toMap()["email"].toString();
        password = data.toMap()["password"].toString();
        co_return QVariant();
    }
    Async::Task<QVariant> put(const QString& endpoint [[maybe_unused]], const QVariant& data = QVariant()) override { co_return QVariant(); }

    QString login;
    QString email;
    QString fullName;
    QString password;
};

void TestRegisterAccount::validData() {
    TestRestApi restApi;
    Controller::Account account(&restApi);
    SignUpDialog signUpDialog(&account);

    auto loginLineEdit = static_cast<QLineEdit*>(signUpDialog.focusWidget());
    loginLineEdit->setText(Login);

    QTest::keyClick(&signUpDialog, Qt::Key_Tab);
    auto fullNameLineEdit = static_cast<QLineEdit*>(signUpDialog.focusWidget());
    fullNameLineEdit->setText(FullName);

    QTest::keyClick(&signUpDialog, Qt::Key_Tab);
    auto emailLineEdit = static_cast<QLineEdit*>(signUpDialog.focusWidget());
    emailLineEdit->setText(Email);

    QTest::keyClick(&signUpDialog, Qt::Key_Tab);
    auto passwordLineEdit = static_cast<QLineEdit*>(signUpDialog.focusWidget());
    passwordLineEdit->setText(Password);

    QTest::keyClick(&signUpDialog, Qt::Key_Tab);
    auto confirmPasswordLineEdit = static_cast<QLineEdit*>(signUpDialog.focusWidget());
    confirmPasswordLineEdit->setText(Password);

    signUpDialog.accept();

    QCOMPARE(restApi.login, Login);
    QCOMPARE(restApi.fullName, FullName);
    QCOMPARE(restApi.email, Email);
    QCOMPARE(restApi.password, Utils::sha256(Password));
}

QTEST_MAIN(TestRegisterAccount)

#include "tst_register_account.moc"
