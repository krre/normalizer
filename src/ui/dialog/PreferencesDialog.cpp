#include "PreferencesDialog.h"
#include "external/settings/Settings.h"
#include <QtWidgets>

PreferencesDialog::PreferencesDialog(const QStringList& adapters, Settings* settings, QWidget* parent) : StandardDialog(parent), m_settings(settings) {
    setWindowTitle(tr("Preferences"));

    auto verticalLayout = new QVBoxLayout;
    verticalLayout->addWidget(createDevelopmentServerGroupBox());
    verticalLayout->addWidget(createGraphicsGroupBox(adapters));

    setContentLayout(verticalLayout);
    resizeToWidth(600);
    m_urlLineEdit->setFocus();
}

void PreferencesDialog::accept() {
    Settings::DevelopmentServer server;
    server.url = m_urlLineEdit->text();
    m_settings->setDevelopmentServer(server);

    Settings::Graphics graphics;
    graphics.adapter = m_adapterComboBox->currentIndex();
    m_settings->setGraphics(graphics);

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

QGroupBox* PreferencesDialog::createGraphicsGroupBox(const QStringList& adapters) {
    m_adapterComboBox = new QComboBox;
    m_adapterComboBox->addItems(adapters);
    m_adapterComboBox->setCurrentIndex(m_settings->graphics().adapter);

    auto layout = new QFormLayout;
    layout->addRow(tr("Adapter:"), m_adapterComboBox);
    layout->itemAt(layout->indexOf(m_adapterComboBox))->setAlignment(Qt::AlignLeft);

    auto groupBox = new QGroupBox(tr("Graphics"));
    groupBox->setLayout(layout);
    return groupBox;
}
