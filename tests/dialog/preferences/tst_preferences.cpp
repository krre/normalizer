#include "ui/dialog/PreferencesDialog.h"
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
    PreferencesDialog::Data data;
    data.host = host;
    data.port = port;

    PreferencesDialog preferencesDialog(data);

    QCOMPARE(preferencesDialog.m_hostLineEdit->text(), data.host.toString());
    QCOMPARE(preferencesDialog.m_portLineEdit->text().toInt(), data.port);
}

void TestPreferences::setSettings() {
    PreferencesDialog preferencesDialog((PreferencesDialog::Data()));
    preferencesDialog.m_hostLineEdit->setText(host.toString());
    preferencesDialog.m_portLineEdit->setText(QString::number(port));
    preferencesDialog.accept();

    PreferencesDialog::Data outputData = preferencesDialog.data();

    QCOMPARE(preferencesDialog.m_hostLineEdit->text(), outputData.host.toString());
    QCOMPARE(preferencesDialog.m_portLineEdit->text().toInt(), outputData.port);
}

QTEST_MAIN(TestPreferences)

#include "tst_preferences.moc"
