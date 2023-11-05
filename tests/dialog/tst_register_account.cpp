#include "ui/dialog/account/RegisterAccountDialog.h"
#include "manager/network/NetworkManager.h"
#include <QTest>
#include <QLineEdit>

constexpr auto Login = "admin";
constexpr auto FullName = "Morpheus";
constexpr auto Email = "admin@example.com";
constexpr auto Password = "qwerty";
constexpr auto Token = "1234567890";

class TestNetworkManager : public NetworkManager {
public:
    Async::Task<QString> createUser(const User& user) override {
        m_user = user;
        co_return Token;
    };

    Async::Task<QString> login(const User& user) override {};

    User m_user;
};

class TestRegisterAccount : public QObject {
    Q_OBJECT
private slots:
    void validData();
};

void TestRegisterAccount::validData() {
    TestNetworkManager networkManager;
    RegisterAccountDialog registerAccountDialog(&networkManager);

    QLineEdit* loginLineEdit = static_cast<QLineEdit*>(registerAccountDialog.focusWidget());
    loginLineEdit->setText(Login);

    QTest::keyClick(&registerAccountDialog, Qt::Key_Tab);

    QLineEdit* fullNameLineEdit = static_cast<QLineEdit*>(registerAccountDialog.focusWidget());
    fullNameLineEdit->setText(FullName);

    QTest::keyClick(&registerAccountDialog, Qt::Key_Tab);

    QLineEdit* emailLineEdit = static_cast<QLineEdit*>(registerAccountDialog.focusWidget());
    emailLineEdit->setText(Email);

    QTest::keyClick(&registerAccountDialog, Qt::Key_Tab);

    QLineEdit* passwordLineEdit = static_cast<QLineEdit*>(registerAccountDialog.focusWidget());
    passwordLineEdit->setText(Password);

    QTest::keyClick(&registerAccountDialog, Qt::Key_Tab);

    QLineEdit* confirmPasswordLineEdit = static_cast<QLineEdit*>(registerAccountDialog.focusWidget());
    confirmPasswordLineEdit->setText(Password);

    registerAccountDialog.accept();

    QCOMPARE(networkManager.m_user.login, Login);
    QCOMPARE(networkManager.m_user.fullName, FullName);
    QCOMPARE(networkManager.m_user.email, Email);
    QCOMPARE(networkManager.m_user.password, Password);
}

QTEST_MAIN(TestRegisterAccount)

#include "tst_register_account.moc"
