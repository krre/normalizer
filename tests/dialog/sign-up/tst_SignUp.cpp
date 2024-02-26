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

class TestSignUp : public QObject {
    Q_OBJECT
private slots:
    void validData();
};

class TestRestApi : public RestApi {
public:
    Async::Task<QVariant> post(const QString& endpoint [[maybe_unused]], const QVariant& data = QVariant()) override {
        login = data.toMap()["login"].toString();
        fullName = data.toMap()["full_name"].toString();
        email = data.toMap()["email"].toString();
        password = data.toMap()["password"].toString();
        co_return QVariant();
    }

    QString login;
    QString email;
    QString fullName;
    QString password;
};

void TestSignUp::validData() {
    TestRestApi restApi;
    Controller::Account account(&restApi);
    SignUpDialog signUpDialog(&account);

    static_cast<QLineEdit*>(signUpDialog.focusWidget())->setText(Login);

    QTest::keyClick(&signUpDialog, Qt::Key_Tab);
    static_cast<QLineEdit*>(signUpDialog.focusWidget())->setText(FullName);

    QTest::keyClick(&signUpDialog, Qt::Key_Tab);
    static_cast<QLineEdit*>(signUpDialog.focusWidget())->setText(Email);

    QTest::keyClick(&signUpDialog, Qt::Key_Tab);
    static_cast<QLineEdit*>(signUpDialog.focusWidget())->setText(Password);

    QTest::keyClick(&signUpDialog, Qt::Key_Tab);
    static_cast<QLineEdit*>(signUpDialog.focusWidget())->setText(Password);

    signUpDialog.accept();

    QCOMPARE(restApi.login, Login);
    QCOMPARE(restApi.fullName, FullName);
    QCOMPARE(restApi.email, Email);
    QCOMPARE(restApi.password, Utils::sha256(Password));
}

QTEST_MAIN(TestSignUp)

#include "tst_SignUp.moc"
