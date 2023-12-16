#include "PreferencesDialog.h"
#include "settings/Settings.h"
#include <QtWidgets>

PreferencesDialog::PreferencesDialog(Settings* settings, QWidget* parent) : StandardDialog(parent), m_settings(settings) {
    setWindowTitle(tr("Preferences"));

    Settings::Server server = settings->server();

    m_urlLineEdit = new QLineEdit(server.url.toString());

    auto formLayout = new QFormLayout;
    formLayout->addRow(tr("URL:"), m_urlLineEdit);

    auto serverGroupBox = new QGroupBox(tr("Norm Developer Server"));
    serverGroupBox->setLayout(formLayout);

    setContentWidget(serverGroupBox);

    resizeToWidth(400);
    m_urlLineEdit->setFocus();
}

void PreferencesDialog::accept() {
    m_settings->setServer(Settings::Server(QUrl(m_urlLineEdit->text())));
    StandardDialog::accept();
}
