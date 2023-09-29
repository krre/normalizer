#include "ProjectEditor.h"
#include <QtWidgets>

ProjectEditor::ProjectEditor(QWidget* parent) : StandardDialog(parent) {
    setWindowTitle(tr("Add Project"));
    setup();
}

ProjectEditor::ProjectEditor(Id id, QWidget* parent) : StandardDialog(parent) {
    setWindowTitle(tr("Edit Project"));
    setup();
}

void ProjectEditor::setup() {
    m_nameLineEdit = new QLineEdit;
    m_descriptionTextEdit = new QPlainTextEdit;

    m_templateComboBox = new QComboBox;
    m_templateComboBox->addItem(tr("Binary"));
    m_templateComboBox->addItem(tr("Library"));

    auto formLayout = new QFormLayout;
    formLayout->addRow(tr("Name:"), m_nameLineEdit);
    formLayout->addRow(tr("Template:"), m_templateComboBox);
    formLayout->addRow(tr("Description:"), m_descriptionTextEdit);

    formLayout->itemAt(formLayout->indexOf(m_templateComboBox))->setAlignment(Qt::AlignLeft);

    setContentLayout(formLayout, false);
    resizeToWidth(800);

    m_nameLineEdit->setFocus();
}
