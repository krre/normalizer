#include "PreferencesDialog.h"
#include <QtWidgets>

PreferencesDialog::PreferencesDialog(AbstractSettingsManager* settingsManager, QWidget* parent) : StandardDialog(parent), m_settingsManager(settingsManager) {
    setWindowTitle(tr("Preferences"));

    AbstractSettingsManager::ServerAddress serverAddress = settingsManager->serverAddress();

    m_hostLineEdit = new QLineEdit(serverAddress.host);
    m_portLineEdit = new QLineEdit(QString::number(serverAddress.port));
    m_portLineEdit->setValidator(new QIntValidator(1, 1 << 16, this));

    auto formLayout = new QFormLayout;
    formLayout->addRow(tr("Host:"), m_hostLineEdit);
    formLayout->addRow(tr("Port:"), m_portLineEdit);

    auto serverGroupBox = new QGroupBox(tr("Norm Developer Server"));
    serverGroupBox->setLayout(formLayout);

    setContentWidget(serverGroupBox);

    resizeToWidth(400);
}

void PreferencesDialog::accept() {
    m_settingsManager->setServerAddress(AbstractSettingsManager::ServerAddress(m_hostLineEdit->text(), m_portLineEdit->text().toInt()));
    StandardDialog::accept();
}
