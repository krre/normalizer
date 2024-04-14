#include "PreferencesDialog.h"
#include "external/settings/Settings.h"
#include <QtWidgets>

PreferencesDialog::PreferencesDialog(Settings* settings, QWidget* parent) : StandardDialog(parent), m_settings(settings) {
    setWindowTitle(tr("Preferences"));

    auto verticalLayout = new QVBoxLayout;
    verticalLayout->addWidget(createNormHostGroupBox());

    setContentLayout(verticalLayout);
    resizeToWidth(600);
    m_urlLineEdit->setFocus();
}

void PreferencesDialog::accept() {
    Settings::NormHost hormHost;
    hormHost.url = m_urlLineEdit->text();
    m_settings->setNormHost(hormHost);

    StandardDialog::accept();
}

QGroupBox* PreferencesDialog::createNormHostGroupBox() {
    m_urlLineEdit = new QLineEdit(m_settings->normHost().url);

    auto layout = new QFormLayout;
    layout->addRow("URL:", m_urlLineEdit);

    auto groupBox = new QGroupBox(tr("Norm Host"));
    groupBox->setLayout(layout);
    return groupBox;
}
