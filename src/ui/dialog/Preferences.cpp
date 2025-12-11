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

    auto workspaceLayout = new BrowseLayout(settings->pathWorkspace());
    m_workDirLineEdit = workspaceLayout->lineEdit();

    m_hostLineEdit = new QLineEdit(settings->networkHost());

    m_portLineEdit = new QSpinBox;
    m_portLineEdit->setMaximum(1);
    m_portLineEdit->setMaximum(1 << 16);
    m_portLineEdit->setValue(settings->networkPort());

    auto networkLayout = new QHBoxLayout;
    networkLayout->addWidget(new QLabel(tr("Host:")));
    networkLayout->addWidget(m_hostLineEdit);
    networkLayout->addWidget(new QLabel(tr("Port:")));
    networkLayout->addWidget(m_portLineEdit);

    auto networkGroupBox = new QGroupBox(tr("Network"));
    networkGroupBox->setLayout(networkLayout);

    auto pathLayout = new QFormLayout;
    pathLayout->addRow(tr("Workspace:"), workspaceLayout);

    auto pathGroupBox = new QGroupBox(tr("Path"));
    pathGroupBox->setLayout(pathLayout);

    m_vulkanCheckBox = new QCheckBox("Vulkan");
    m_vulkanCheckBox->setChecked(settings->loggingVulkan());

    auto loggingLayout = new QVBoxLayout;
    loggingLayout->addWidget(m_vulkanCheckBox);

    auto loggingGroupBox = new QGroupBox(tr("Logging"));
    loggingGroupBox->setLayout(loggingLayout);

    auto contentLayout = new QVBoxLayout;
    contentLayout->addWidget(uiGroupBox);
    contentLayout->addWidget(networkGroupBox);
    contentLayout->addWidget(pathGroupBox);
    contentLayout->addWidget(loggingGroupBox);

    setContentLayout(contentLayout);

    resizeToWidth(500);
    readSettings();
}

void Preferences::accept() {
    writeSettings();
    StandardDialog::accept();
}

void Preferences::readSettings() {
}

void Preferences::writeSettings() {
    m_settings->setUiLoadLastProject(m_loadLastProjectCheckBox->isChecked());
    m_settings->setNetworkHost(m_portLineEdit->text());
    m_settings->setNetworkPort(m_portLineEdit->value());
    m_settings->setPathWorkspace(m_workDirLineEdit->text());
    m_settings->setLoggingVulkan(m_vulkanCheckBox->isChecked());
}
