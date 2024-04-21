#include "PreferencesDialog.h"
#include "external/settings/Settings.h"
#include <QtWidgets>

PreferencesDialog::PreferencesDialog(Settings* settings, QWidget* parent) : StandardDialog(parent), m_settings(settings) {
    setWindowTitle(tr("Preferences"));

    auto verticalLayout = new QVBoxLayout;
    verticalLayout->addWidget(createDevelopmentServerGroupBox());

    setContentLayout(verticalLayout);
    resizeToWidth(600);
    m_urlLineEdit->setFocus();
}

void PreferencesDialog::accept() {
    Settings::DevelopmentServer server;
    server.url = m_urlLineEdit->text();
    m_settings->setDevelopmentServer(server);

    StandardDialog::accept();
}

QGroupBox* PreferencesDialog::createDevelopmentServerGroupBox() {
    m_urlLineEdit = new QLineEdit(m_settings->developmentServer().url);

    auto layout = new QFormLayout;
    layout->addRow("URL:", m_urlLineEdit);

    auto groupBox = new QGroupBox(tr("Development Server"));
    groupBox->setLayout(layout);
    return groupBox;
}
