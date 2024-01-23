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

    using namespace Controller;

    if (m_state == State::Add) {
        m_targetComboBox = new QComboBox;
        m_targetComboBox->addItems({ Project::targetString(Project::Target::Application),
                                    Project::targetString(Project::Target::Library) });

        formLayout->addRow(tr("Target:"), m_targetComboBox);
        formLayout->itemAt(formLayout->indexOf(m_targetComboBox))->setAlignment(Qt::AlignLeft);
    } else {
        m_targetLabel = new QLabel;
        formLayout->addRow(tr("Target:"), m_targetLabel);
    }

    formLayout->addRow(tr("Description:"), m_descriptionTextEdit);

    setContentLayout(formLayout, false);
    resizeToWidth(800);

    m_nameLineEdit->setFocus();
}

Async::Task<void> ProjectEditor::createProject() {
    Controller::Project::CreateRequest project;
    project.name = m_nameLineEdit->text();
    project.target = static_cast<Controller::Project::Target>(m_targetComboBox->currentIndex());
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
    m_targetLabel->setText(Controller::Project::targetString(project.target));
    m_descriptionTextEdit->setPlainText(project.description);
}
