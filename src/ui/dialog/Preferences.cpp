#include "Preferences.h"
#include "ui/widget/BrowseLayout.h"
#include "settings/Settings.h"
#include <QGroupBox>
#include <QLineEdit>
#include <QCheckBox>
#include <QFormLayout>

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
    m_settings->setPathWorkspace(m_workDirLineEdit->text());
    m_settings->setLoggingVulkan(m_vulkanCheckBox->isChecked());
}
