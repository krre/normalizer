#include "PreferencesDialog.h"
#include <QtWidgets>

PreferencesDialog::PreferencesDialog(Settings* settings, QWidget* parent) : StandardDialog(parent), m_settings(settings) {
    setWindowTitle(tr("Preferences"));

    Settings::ServerAddress serverAddress = settings->serverAddress();

    m_urlLineEdit = new QLineEdit(serverAddress.url.toString());

    auto formLayout = new QFormLayout;
    formLayout->addRow(tr("URL:"), m_urlLineEdit);

    auto serverGroupBox = new QGroupBox(tr("Norm Developer Server"));
    serverGroupBox->setLayout(formLayout);

    setContentWidget(serverGroupBox);

    resizeToWidth(400);
    m_urlLineEdit->setFocus();
}

void PreferencesDialog::accept() {
    m_settings->setServerAddress(Settings::ServerAddress(QUrl(m_urlLineEdit->text())));
    StandardDialog::accept();
}
