#include "PreferencesDialog.h"
#include "ui/widget/BrowseLayout.h"
#include "external/settings/Settings.h"
#include <QtWidgets>

PreferencesDialog::PreferencesDialog(Settings* settings, QWidget* parent) : StandardDialog(parent), m_settings(settings) {
    setWindowTitle(tr("Preferences"));
    setContentWidget(createProjectLocationGroupBox());
    resizeToWidth(600);
    m_workspaceBrowseLayout->setFocus();
}

void PreferencesDialog::accept() {
    Settings::ProjectLocation projectLocation;
    projectLocation.workspace = m_workspaceBrowseLayout->text();
    projectLocation.host = m_hostLineEdit->text();

    m_settings->setProjectLocation(projectLocation);
    StandardDialog::accept();
}

QGroupBox* PreferencesDialog::createProjectLocationGroupBox() {
    m_workspaceBrowseLayout = new BrowseLayout(m_settings->projectLocation().workspace);
    m_hostLineEdit = new QLineEdit(m_settings->projectLocation().host);

    auto layout = new QFormLayout;
    layout->addRow(tr("Local workspace:"), m_workspaceBrowseLayout);
    layout->addRow(tr("Remote host:"), m_hostLineEdit);

    auto groupBox = new QGroupBox(tr("Project Location"));
    groupBox->setLayout(layout);
    return groupBox;
}
