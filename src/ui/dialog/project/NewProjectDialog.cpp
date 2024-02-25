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
    m_workspaceBrowseLayout = new BrowseLayout(m_settings->projectLocation().workspace);

    m_targetComboBox = new QComboBox;
    m_targetComboBox->addItems({
        Project::targetString(Project::Target::Application),
        Project::targetString(Project::Target::Library)
    });

    auto formLayout = new QFormLayout;
    formLayout->addRow(tr("Name:"), m_nameLineEdit);
    formLayout->addRow(tr("Description:"), m_descriptionLineEdit);
    formLayout->addRow(tr("Workspace:"), m_workspaceBrowseLayout);
    formLayout->addRow(tr("Target:"), m_targetComboBox);

    formLayout->itemAt(formLayout->indexOf(m_targetComboBox))->setAlignment(Qt::AlignLeft);

    setContentLayout(formLayout, false);
    resizeToWidth(500);

    m_nameLineEdit->setFocus();
    enableOkButton();
}

void NewProjectDialog::accept() {
    StandardDialog::accept();
}

void NewProjectDialog::enableOkButton() {
    buttonBox()->button(QDialogButtonBox::Ok)->setEnabled(!m_nameLineEdit->text().isEmpty());
}
