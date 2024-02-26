#include "ui/dialog/account/AccountDialog.h"
#include "external/repository/network/controller/account/Account.h"
#include "external/repository/network/RestApi.h"
#include <QTest>
#include <QLineEdit>

constexpr auto Login = "admin";
constexpr auto Email = "admin@example.com";
constexpr auto FullName = "Admin";

class TestRestApi : public RestApi {
public:
    Async::Task<QVariant> get(const QString& endpoint [[maybe_unused]], const QUrlQuery& query = QUrlQuery()) override {
        co_return QVariantMap({
            { "login", Login },
            { "email", Email },
            { "full_name", FullName }
        });
    }

    Async::Task<QVariant> put(const QString& endpoint [[maybe_unused]], const QVariant& data = QVariant()) override {
        fullName = data.toMap()["full_name"].toString();
        co_return QVariant();
    }

    QString fullName;
};

class TestAccountDialog : public QObject {
    Q_OBJECT
private slots:
    void init() {
        Async::Ready = true;
    }

    void getData();
    void updateData();
};

void TestAccountDialog::getData() {
    TestRestApi restApi;
    Controller::Account account(&restApi);
    AccountDialog accountDialog(&account);

    auto fullNameLineEdit = static_cast<QLineEdit*>(accountDialog.focusWidget());

    QTest::keyClick(&accountDialog, Qt::Key_Backtab);
    auto emailLineEdit = static_cast<QLineEdit*>(accountDialog.focusWidget());

    QTest::keyClick(&accountDialog, Qt::Key_Backtab);
    auto loginLineEdit = static_cast<QLineEdit*>(accountDialog.focusWidget());

    accountDialog.accept();

    QCOMPARE(fullNameLineEdit->text(), FullName);
    QCOMPARE(emailLineEdit->text(), Email);
    QCOMPARE(loginLineEdit->text(), Login);
}

void TestAccountDialog::updateData() {
    TestRestApi restApi;
    Controller::Account account(&restApi);
    AccountDialog accountDialog(&account);

    static_cast<QLineEdit*>(accountDialog.focusWidget())->setText(FullName);

    accountDialog.accept();

    QCOMPARE(restApi.fullName, FullName);
}

QTEST_MAIN(TestAccountDialog)

#include "TestAccount.moc"
