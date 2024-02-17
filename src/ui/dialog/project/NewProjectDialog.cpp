#include "NewProjectDialog.h"
#include "ui/widget/BrowseLayout.h"
#include "external/settings/Settings.h"
#include "program/Project.h"
#include <QtWidgets>

NewProjectDialog::NewProjectDialog(Settings* settings) : m_settings(settings) {
    setWindowTitle(tr("New Project"));

    m_nameLineEdit = new QLineEdit;
    connect(m_nameLineEdit, &QLineEdit::textChanged, this, &NewProjectDialog::enableOkButton);

    m_descriptionLineEdit = new QLineEdit;

    m_targetComboBox = new QComboBox;
    m_targetComboBox->addItems({
        Project::targetString(Project::Target::Application),
        Project::targetString(Project::Target::Library)
    });

    m_locationComboBox = new QComboBox;
    m_locationComboBox->addItems({
        Project::locationString(Project::Location::Local),
        Project::locationString(Project::Location::Remote)
    });

    connect(m_locationComboBox, &QComboBox::currentIndexChanged, this, &NewProjectDialog::switchLocation);

    m_directoryBrowseLayout = new BrowseLayout(m_settings->projectLocation().directory);
    m_hostLineEdit = new QLineEdit(m_settings->projectLocation().host);

    m_formLayout = new QFormLayout;
    m_formLayout->addRow(tr("Name:"), m_nameLineEdit);
    m_formLayout->addRow(tr("Description:"), m_descriptionLineEdit);
    m_formLayout->addRow(tr("Target:"), m_targetComboBox);
    m_formLayout->addRow(tr("Location:"), m_locationComboBox);
    m_formLayout->addRow(tr("Directory:"), m_directoryBrowseLayout);
    m_formLayout->addRow(tr("Host:"), m_hostLineEdit);

    m_formLayout->itemAt(m_formLayout->indexOf(m_targetComboBox))->setAlignment(Qt::AlignLeft);
    m_formLayout->itemAt(m_formLayout->indexOf(m_locationComboBox))->setAlignment(Qt::AlignLeft);

    setContentLayout(m_formLayout, false);
    switchLocation();
    resizeToWidth(500);

    m_nameLineEdit->setFocus();
    enableOkButton();
}

NewProjectDialog::~NewProjectDialog() {
    Settings::ProjectLocation projectLocation;
    projectLocation.directory = m_directoryBrowseLayout->text();
    projectLocation.host = m_hostLineEdit->text();

    m_settings->setProjectLocation(projectLocation);
}

void NewProjectDialog::enableOkButton() {
    buttonBox()->button(QDialogButtonBox::Ok)->setEnabled(!m_nameLineEdit->text().isEmpty());
}

void NewProjectDialog::switchLocation() {
    if (m_locationComboBox->currentIndex() == int(Project::Location::Local)) {
        m_formLayout->setRowVisible(m_hostLineEdit, false);
        m_formLayout->setRowVisible(m_directoryBrowseLayout, true);
    } else {
        m_formLayout->setRowVisible(m_directoryBrowseLayout, false);
        m_formLayout->setRowVisible(m_hostLineEdit, true);
    }
}
