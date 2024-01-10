#include "ProjectEditor.h"
#include "external/network/controller/project/Project.h"
#include <QtWidgets>

ProjectEditor::ProjectEditor(Controller::Project* project, QWidget* parent) :
        StandardDialog(parent), m_project(project), m_state(State::Add) {
    setWindowTitle(tr("Create Project"));
    createForm();
}

ProjectEditor::ProjectEditor(Controller::Project* project, Id id, QWidget* parent) : StandardDialog(parent), m_project(project), m_id(id), m_state(State::Edit) {
    setWindowTitle(tr("Edit Project"));
    createForm();
    m_templateComboBox->setEnabled(false);
    getProject();
}

void ProjectEditor::accept() {
    if (m_state == State::Edit) {
        updateProject();
    } else {
        createProject();
    }
}

void ProjectEditor::createForm() {
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

Async::Task<void> ProjectEditor::createProject() {
    Controller::Project::CreateProject project;
    project.name = m_nameLineEdit->text();
    project.projectTemplate = static_cast<Controller::Project::Template>(m_templateComboBox->currentIndex());
    project.description = m_descriptionTextEdit->toPlainText();

    co_await m_project->create(project);
    StandardDialog::accept();
}

Async::Task<void> ProjectEditor::updateProject() {
    Controller::Project::UpdateProject project;
    project.name = m_nameLineEdit->text();
    project.description = m_descriptionTextEdit->toPlainText();

    co_await m_project->update(m_id, project);
    StandardDialog::accept();
}

Async::Task<void> ProjectEditor::getProject() {
    Controller::Project::GetProject project = co_await m_project->getOne(m_id);
    m_nameLineEdit->setText(project.name);
    m_templateComboBox->setCurrentIndex(int(project.projectTemplate));
    m_descriptionTextEdit->setPlainText(project.description);
}
