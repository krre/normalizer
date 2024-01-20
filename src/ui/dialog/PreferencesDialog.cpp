#include "PreferencesDialog.h"
#include "external/settings/Settings.h"
#include <QtWidgets>

PreferencesDialog::PreferencesDialog(Settings* settings, QWidget* parent) : StandardDialog(parent), m_settings(settings) {
    setWindowTitle(tr("Preferences"));

    Settings::Server server = settings->server();

    m_apilLineEdit = new QLineEdit(server.api.toString());

    auto formLayout = new QFormLayout;
    formLayout->addRow("API:", m_apilLineEdit);

    auto urlGroupBox = new QGroupBox("Server");
    urlGroupBox->setLayout(formLayout);

    setContentWidget(urlGroupBox);

    resizeToWidth(400);
    m_apilLineEdit->setFocus();
}

void PreferencesDialog::accept() {
    Settings::Server server;
    server.api = QUrl(m_apilLineEdit->text());

    m_settings->setServer(server);
    StandardDialog::accept();
}
