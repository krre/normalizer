#include "NewProject.h"
#include "ui/component/BrowseLineEdit.h"
#include "project/ProjectSettings.h"
#include "project/ProjectManager.h"
#include "core/Settings.h"
#include "core/Global.h"
#include "core/Constants.h"
#include <QtWidgets>

namespace Dialog {

NewProject::NewProject() {
    setWindowTitle(tr("New Project"));

    auto projectGroupBox = createProjectGroupBox();
    targetGroupBox = createTargetGroupBox();

    auto verticalLayout = new QVBoxLayout;
    verticalLayout->addWidget(projectGroupBox);
    verticalLayout->addWidget(targetGroupBox);

    setContentLayout(verticalLayout);
    resizeToWidth(500);
    adjustAcceptedButton();
    projectNameLineEdit->setFocus();
}

QString NewProject::path() const {
    return projectDirectoryBrowseLineEdit->text() + "/" + projectNameLineEdit->text();
}

Norm::Project::Target NewProject::target() const {
    return static_cast<Norm::Project::Target>(targetTypeComboBox->currentIndex());
}

void NewProject::adjustAcceptedButton() {
    setOkButtonEnabled(!projectNameLineEdit->text().isEmpty() && !projectDirectoryBrowseLineEdit->text().isEmpty());
}

QGroupBox* NewProject::createProjectGroupBox() {
    projectNameLineEdit = new QLineEdit;
    connect(projectNameLineEdit, &QLineEdit::textChanged, this, &NewProject::onProjectNameChanged);

    projectDirectoryBrowseLineEdit = new BrowseLineEdit(Settings::Project::workspace());
    connect(projectDirectoryBrowseLineEdit, &BrowseLineEdit::textChanged, this, &NewProject::adjustAcceptedButton);

    auto layout = new QFormLayout;
    layout->addRow(tr("Name:"), projectNameLineEdit);
    layout->addRow(tr("Directory:"), projectDirectoryBrowseLineEdit);

    auto result = new QGroupBox(tr("Project"));
    result->setLayout(layout);

    return result;
}

QGroupBox* NewProject::createTargetGroupBox() {
    targetNameLineEdit = new QLineEdit;

    targetTypeComboBox = new QComboBox;
    targetTypeComboBox->addItem(Const::Project::Target::Application::Name);
    targetTypeComboBox->addItem(Const::Project::Target::Library::Name);

    auto layout = new QFormLayout;
    layout->addRow(tr("Name:"), targetNameLineEdit);
    layout->addRow(tr("Type:"), targetTypeComboBox);
    layout->itemAt(1, QFormLayout::FieldRole)->setAlignment(Qt::AlignLeft);

    targetGroupBox = new QGroupBox(tr("Target"));
    targetGroupBox->setCheckable(true);
    targetGroupBox->setChecked(true);
    targetGroupBox->setLayout(layout);

    return targetGroupBox;
}

void NewProject::accept() {
    QDir dir(path());

    if (dir.exists()) {
        QMessageBox::critical(this, tr("Create Project"), tr("Project already exists"));
        return;
    }

    dir.mkpath(path());

    auto projectSettings = Global::projectSettings();
    projectSettings->setProjectPath(path());
    projectSettings->create();
    projectSettings->save();
    projectSettings->clear();

    Global::project()->create(path(), target());
    StandardDialog::accept();
}

void NewProject::onProjectNameChanged(const QString& projectName) {
    adjustAcceptedButton();

    if (targetGroupBox->isChecked() && targetNameLineEdit->text() == oldProjectName) {
        targetNameLineEdit->setText(projectName);
    }

    oldProjectName = projectName;
}

}
