#include "NewProjectDialog.h"
#include "ui/widget/BrowseLayout.h"
#include "external/network/controller/project/Project.h"
#include <QtWidgets>

NewProjectDialog::NewProjectDialog() {
    setWindowTitle(tr("New Project"));

    using namespace Controller;

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

    m_directoryBrowseLayout = new BrowseLayout;

    auto formLayout = new QFormLayout;
    formLayout->addRow(tr("Name:"), m_nameLineEdit);
    formLayout->addRow(tr("Description:"), m_descriptionLineEdit);
    formLayout->addRow(tr("Target:"), m_targetComboBox);
    formLayout->addRow(tr("Location:"), m_locationComboBox);
    formLayout->addRow(tr("Directory:"), m_directoryBrowseLayout);

    formLayout->itemAt(formLayout->indexOf(m_targetComboBox))->setAlignment(Qt::AlignLeft);
    formLayout->itemAt(formLayout->indexOf(m_locationComboBox))->setAlignment(Qt::AlignLeft);

    setContentLayout(formLayout, false);
    resizeToWidth(500);

    m_nameLineEdit->setFocus();
    enableOkButton();

    connect(m_locationComboBox, &QComboBox::currentIndexChanged, this, [=, this] {
        formLayout->setRowVisible(m_directoryBrowseLayout, m_locationComboBox->currentIndex() == int(Project::Location::Local));
    });
}

void NewProjectDialog::enableOkButton() {
    buttonBox()->button(QDialogButtonBox::Ok)->setEnabled(!m_nameLineEdit->text().isEmpty());
}
