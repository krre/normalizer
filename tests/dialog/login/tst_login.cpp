#include "ui/dialog/account/LoginDialog.h"
#include "external/repository/network/controller/account/Account.h"
#include "external/repository/network/RestApi.h"
#include "core/Utils.h"
#include <QTest>
#include <QLineEdit>

constexpr auto Email = "admin@example.com";
constexpr auto Password = "qwerty";

class TestRestApi : public RestApi {
public:
    Async::Task<QVariant> get(const QString& endpoint [[maybe_unused]], const QUrlQuery& query = QUrlQuery()) override { co_return QVariant(); }
    Async::Task<QVariant> del(const QString& endpoint [[maybe_unused]]) override { co_return QVariant(); }
    Async::Task<QVariant> post(const QString& endpoint [[maybe_unused]], const QVariant& data = QVariant()) override {
        email = data.toMap()["email"].toString();
        password = data.toMap()["password"].toString();
        co_return QVariant();
    }
    Async::Task<QVariant> put(const QString& endpoint [[maybe_unused]], const QVariant& data = QVariant()) override { co_return QVariant(); }

    QString email;
    QString password;
};


class TestLogin : public QObject {
    Q_OBJECT
private slots:
    void validData();
};

void TestLogin::validData() {
    TestRestApi restApi;
    Controller::Account account(&restApi);
    LoginDialog loginDialog(&account);

    auto emailLineEdit = static_cast<QLineEdit*>(loginDialog.focusWidget());
    emailLineEdit->setText(Email);

    QTest::keyClick(&loginDialog, Qt::Key_Tab);
    auto passwordLineEdit = static_cast<QLineEdit*>(loginDialog.focusWidget());
    passwordLineEdit->setText(Password);

    loginDialog.accept();

    QCOMPARE(restApi.email, Email);
    QCOMPARE(restApi.password, Utils::sha256(Password));
}

QTEST_MAIN(TestLogin)

#include "tst_login.moc"
