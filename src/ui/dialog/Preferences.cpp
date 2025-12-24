#include "Preferences.h"
#include "ui/widget/BrowseLayout.h"
#include "settings/Settings.h"
#include <QGroupBox>
#include <QLineEdit>
#include <QCheckBox>
#include <QSpinBox>
#include <QLabel>
#include <QFormLayout>
#include <QIntValidator>

Preferences::Preferences(Settings* settings) : m_settings(settings) {
    setWindowTitle(tr("Preferences"));

    m_loadLastProjectCheckBox = new QCheckBox(tr("Load last project"));
    m_loadLastProjectCheckBox->setChecked(settings->uiLoadLastProject());

    auto uiLayout = new QVBoxLayout;
    uiLayout->addWidget(m_loadLastProjectCheckBox);

    auto uiGroupBox = new QGroupBox(tr("User Interface"));
    uiGroupBox->setLayout(uiLayout);

    m_hostLineEdit = new QLineEdit(settings->serverHost());

    m_portLineEdit = new QSpinBox;
    m_portLineEdit->setMaximum(1);
    m_portLineEdit->setMaximum(1 << 16);
    m_portLineEdit->setValue(settings->serverPort());

    auto serverLayout = new QHBoxLayout;
    serverLayout->addWidget(new QLabel(tr("Host:")));
    serverLayout->addWidget(m_hostLineEdit);
    serverLayout->addWidget(new QLabel(tr("Port:")));
    serverLayout->addWidget(m_portLineEdit);

    auto serverGroupBox = new QGroupBox(tr("Server"));
    serverGroupBox->setLayout(serverLayout);

    m_vulkanCheckBox = new QCheckBox("Vulkan");
    m_vulkanCheckBox->setChecked(settings->loggingVulkan());

    auto loggingLayout = new QVBoxLayout;
    loggingLayout->addWidget(m_vulkanCheckBox);

    auto loggingGroupBox = new QGroupBox(tr("Logging"));
    loggingGroupBox->setLayout(loggingLayout);

    auto contentLayout = new QVBoxLayout;
    contentLayout->addWidget(uiGroupBox);
    contentLayout->addWidget(serverGroupBox);
    contentLayout->addWidget(loggingGroupBox);

    setContentLayout(contentLayout);

    resizeToWidth(500);
}

void Preferences::accept() {
    writeSettings();
    StandardDialog::accept();
}

void Preferences::writeSettings() {
    m_settings->setUiLoadLastProject(m_loadLastProjectCheckBox->isChecked());
    m_settings->setServerHost(m_hostLineEdit->text());
    m_settings->setServerPort(m_portLineEdit->value());
    m_settings->setLoggingVulkan(m_vulkanCheckBox->isChecked());
}
