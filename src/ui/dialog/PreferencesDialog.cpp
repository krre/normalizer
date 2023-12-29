#include "PreferencesDialog.h"
#include "settings/Settings.h"
#include <QtWidgets>

PreferencesDialog::PreferencesDialog(Settings* settings, QWidget* parent) : StandardDialog(parent), m_settings(settings) {
    setWindowTitle(tr("Preferences"));

    Settings::Server server = settings->server();

    m_apiUrlLineEdit = new QLineEdit(server.api.toString());
    m_editorUrlLineEdit = new QLineEdit(server.editor.toString());

    auto formLayout = new QFormLayout;
    formLayout->addRow(tr("API URL:"), m_apiUrlLineEdit);
    formLayout->addRow(tr("Editor URL:"), m_editorUrlLineEdit);

    auto serverGroupBox = new QGroupBox(tr("Norm Developer Server"));
    serverGroupBox->setLayout(formLayout);

    setContentWidget(serverGroupBox);

    resizeToWidth(400);
    m_apiUrlLineEdit->setFocus();
}

void PreferencesDialog::accept() {
    Settings::Server server;
    server.api = QUrl(m_apiUrlLineEdit->text());
    server.editor = QUrl(m_editorUrlLineEdit->text());

    m_settings->setServer(server);
    StandardDialog::accept();
}
