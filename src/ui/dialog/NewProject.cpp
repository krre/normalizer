#include "NewProject.h"
#include "core/ObjectNames.h"
#include <QtWidgets>

NewProject::NewProject(QWidget* parent) : StandardDialog(parent) {
    setWindowTitle(tr("New Project"));
    m_nameLineEdit = new QLineEdit;
    m_nameLineEdit->setObjectName(ObjectName::Name);

    m_templateComboBox = new QComboBox;
    m_templateComboBox->setObjectName(ObjectName::Template);
    m_templateComboBox->addItem(tr("Binary"));
    m_templateComboBox->addItem(tr("Library"));

    auto formLayout = new QFormLayout;
    formLayout->addRow(new QLabel(tr("Name:")), m_nameLineEdit);
    formLayout->addRow(new QLabel(tr("Template:")), m_templateComboBox);

    formLayout->itemAt(formLayout->indexOf(m_templateComboBox))->setAlignment(Qt::AlignLeft);

    setContentLayout(formLayout);
    resizeToWidth(400);

    connect(m_nameLineEdit, &QLineEdit::textChanged, this, &NewProject::adjustAcceptedButton);

    adjustAcceptedButton();
    m_nameLineEdit->setFocus();
}

QString NewProject::name() const {
    return m_nameLineEdit->text();
}

Norm::Project::Template NewProject::projectTemplate() const {
    return static_cast<Norm::Project::Template>(m_templateComboBox->currentIndex());
}

void NewProject::adjustAcceptedButton() {
    buttonBox()->button(QDialogButtonBox::Ok)->setEnabled(!m_nameLineEdit->text().isEmpty());
}
