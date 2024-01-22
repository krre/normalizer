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

    auto formLayout = new QFormLayout;
    formLayout->addRow(tr("Name:"), m_nameLineEdit);

    if (m_state == State::Add) {
        m_templateComboBox = new QComboBox;
        m_templateComboBox->addItems(m_templates);

        formLayout->addRow(tr("Template:"), m_templateComboBox);
        formLayout->itemAt(formLayout->indexOf(m_templateComboBox))->setAlignment(Qt::AlignLeft);
    } else {
        m_templateLabel = new QLabel;
        formLayout->addRow(tr("Template:"), m_templateLabel);
    }

    formLayout->addRow(tr("Description:"), m_descriptionTextEdit);

    setContentLayout(formLayout, false);
    resizeToWidth(800);

    m_nameLineEdit->setFocus();
}

Async::Task<void> ProjectEditor::createProject() {
    Controller::Project::CreateRequest project;
    project.name = m_nameLineEdit->text();
    project.projectTemplate = static_cast<Controller::Project::Template>(m_templateComboBox->currentIndex());
    project.description = m_descriptionTextEdit->toPlainText();

    co_await m_project->create(project);
    StandardDialog::accept();
}

Async::Task<void> ProjectEditor::updateProject() {
    Controller::Project::UpdateRequest project;
    project.name = m_nameLineEdit->text();
    project.description = m_descriptionTextEdit->toPlainText();

    co_await m_project->update(m_id, project);
    StandardDialog::accept();
}

Async::Task<void> ProjectEditor::getProject() {
    Controller::Project::GetResponse project = co_await m_project->getOne(m_id);
    m_nameLineEdit->setText(project.name);
    m_templateLabel->setText(m_templates.at(int(project.projectTemplate)));
    m_descriptionTextEdit->setPlainText(project.description);
}
