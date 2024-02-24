#include "PreferencesDialog.h"
#include "ui/widget/BrowseLayout.h"
#include "external/settings/Settings.h"
#include <QtWidgets>

PreferencesDialog::PreferencesDialog(Settings* settings, QWidget* parent) : StandardDialog(parent), m_settings(settings) {
    setWindowTitle(tr("Preferences"));

    Settings::ProjectLocation projectLocation = settings->projectLocation();

    m_directoryBrowseLayout = new BrowseLayout(settings->projectLocation().directory);
    m_hostLineEdit = new QLineEdit(projectLocation.host);

    auto formLayout = new QFormLayout;
    formLayout->addRow("Local directory:", m_directoryBrowseLayout);
    formLayout->addRow("Remote host:", m_hostLineEdit);

    auto projectLocationGroupBox = new QGroupBox("Project Location");
    projectLocationGroupBox->setLayout(formLayout);

    setContentWidget(projectLocationGroupBox);

    resizeToWidth(600);
    m_directoryBrowseLayout->setFocus();
}

void PreferencesDialog::accept() {
    Settings::ProjectLocation projectLocation;
    projectLocation.directory = m_directoryBrowseLayout->text();
    projectLocation.host = m_hostLineEdit->text();

    m_settings->setProjectLocation(projectLocation);
    StandardDialog::accept();
}
