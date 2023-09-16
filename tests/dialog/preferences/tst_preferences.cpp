#include "ui/dialog/Preferences.h"
#include <QTest>
#include <QLineEdit>

const QHostAddress host = QHostAddress(QHostAddress::LocalHost);
constexpr auto port = 3128;

class TestPreferences : public QObject {
    Q_OBJECT
private slots:
    void readSettings();
    void setSettings();
};

void TestPreferences::readSettings() {
    Preferences::Data data;
    data.host = host;
    data.port = port;

    Preferences preferences(data);

    QCOMPARE(preferences.m_hostLineEdit->text(), data.host.toString());
    QCOMPARE(preferences.m_portLineEdit->text().toInt(), data.port);
}

void TestPreferences::setSettings() {
    Preferences preferences((Preferences::Data()));
    preferences.m_hostLineEdit->setText(host.toString());
    preferences.m_portLineEdit->setText(QString::number(port));
    preferences.accept();

    Preferences::Data outputData = preferences.data();

    QCOMPARE(preferences.m_hostLineEdit->text(), outputData.host.toString());
    QCOMPARE(preferences.m_portLineEdit->text().toInt(), outputData.port);
}

QTEST_MAIN(TestPreferences)

#include "tst_preferences.moc"
