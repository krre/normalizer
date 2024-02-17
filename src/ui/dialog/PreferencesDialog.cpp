#include "PreferencesDialog.h"
#include "ui/widget/BrowseLayout.h"
#include "external/settings/Settings.h"
#include <QtWidgets>

PreferencesDialog::PreferencesDialog(Settings* settings, QWidget* parent) : StandardDialog(parent), m_settings(settings) {
    setWindowTitle(tr("Preferences"));

    Settings::NewProject newProject = settings->newProject();

    m_directoryBrowseLayout = new BrowseLayout(settings->newProject().directory);
    m_hostLineEdit = new QLineEdit(newProject.host);

    auto formLayout = new QFormLayout;
    formLayout->addRow("Local directory:", m_directoryBrowseLayout);
    formLayout->addRow("Remote host:", m_hostLineEdit);

    auto urlGroupBox = new QGroupBox("Project Location");
    urlGroupBox->setLayout(formLayout);

    setContentWidget(urlGroupBox);

    resizeToWidth(600);
    m_directoryBrowseLayout->setFocus();
}

void PreferencesDialog::accept() {
    Settings::NewProject newProject;
    newProject.directory = m_directoryBrowseLayout->text();
    newProject.host = m_hostLineEdit->text();

    m_settings->setNewProject(newProject);
    StandardDialog::accept();
}
