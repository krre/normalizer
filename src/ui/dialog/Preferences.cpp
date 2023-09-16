#include "Preferences.h"
#include <QtWidgets>

Preferences::Preferences(const Data& data, QWidget* parent) : StandardDialog(parent) {
    setWindowTitle(tr("Preferences"));

    m_hostLineEdit = new QLineEdit(data.host.toString());
    m_portLineEdit = new QLineEdit(QString::number(data.port));
    m_portLineEdit->setValidator(new QIntValidator(1, 1 << 16, this));

    auto formLayout = new QFormLayout;
    formLayout->addRow(tr("Host:"), m_hostLineEdit);
    formLayout->addRow(tr("Port:"), m_portLineEdit);

    auto serverGroupBox = new QGroupBox(tr("Norm Developer Server"));
    serverGroupBox->setLayout(formLayout);

    setContentWidget(serverGroupBox);

    resizeToWidth(400);
}

Preferences::Data Preferences::data() const {
    Data result;
    result.host = QHostAddress(m_hostLineEdit->text());
    result.port = m_portLineEdit->text().toInt();

    return result;
}
