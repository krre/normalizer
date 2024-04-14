#include "NewProjectDialog.h"
#include "ui/widget/BrowseLayout.h"
#include "external/process/Process.h"
#include "external/settings/Settings.h"
#include <QtWidgets>

NewProjectDialog::NewProjectDialog(Process* process, Settings* settings) : m_process(process), m_settings(settings) {
    setWindowTitle(tr("New Project"));

    m_nameLineEdit = new QLineEdit;
    connect(m_nameLineEdit, &QLineEdit::textChanged, this, &NewProjectDialog::enableOkButton);

    m_workspaceBrowseLayout = new BrowseLayout("");

    m_targetComboBox = new QComboBox;
    m_targetComboBox->addItems({
        Project::targetString(Project::Target::Application),
        Project::targetString(Project::Target::Library)
    });

    auto formLayout = new QFormLayout;
    formLayout->addRow(tr("Name:"), m_nameLineEdit);
    formLayout->addRow(tr("Workspace:"), m_workspaceBrowseLayout);
    formLayout->addRow(tr("Target:"), m_targetComboBox);

    formLayout->itemAt(formLayout->indexOf(m_targetComboBox))->setAlignment(Qt::AlignLeft);

    setContentLayout(formLayout, false);
    resizeToWidth(500);

    m_nameLineEdit->setFocus();
    enableOkButton();
}

void NewProjectDialog::accept() {
    m_process->createProject(m_nameLineEdit->text(), m_workspaceBrowseLayout->text(), static_cast<Project::Target>(m_targetComboBox->currentIndex()));
    StandardDialog::accept();
}

void NewProjectDialog::enableOkButton() {
    buttonBox()->button(QDialogButtonBox::Ok)->setEnabled(!m_nameLineEdit->text().isEmpty());
}
