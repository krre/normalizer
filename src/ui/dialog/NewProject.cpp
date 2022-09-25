#include "NewProject.h"
#include "ui/component/BrowseLineEdit.h"
#include "project/ProjectSettings.h"
#include "core/Settings.h"
#include "core/Global.h"
#include "core/Constants.h"
#include <QtWidgets>

namespace Dialog {

NewProject::NewProject() {
    setWindowTitle(tr("New Project"));

    nameLineEdit = new QLineEdit;
    connect(nameLineEdit, &QLineEdit::textChanged, this, &NewProject::adjustAcceptedButton);

    directoryBrowseLineEdit = new BrowseLineEdit(Settings::Project::workspace());
    connect(directoryBrowseLineEdit, &BrowseLineEdit::textChanged, this, &NewProject::adjustAcceptedButton);

    targetComboBox = new QComboBox;
    targetComboBox->addItem(Const::Project::Target::Application::Name);
    targetComboBox->addItem(Const::Project::Target::Library::Name);

    auto formLayout = new QFormLayout;
    formLayout->addRow(new QLabel(tr("Name:")), nameLineEdit);
    formLayout->addRow(new QLabel(tr("Directory:")), directoryBrowseLineEdit);

    formLayout->addRow(new QLabel(tr("Target:")), targetComboBox);
    formLayout->itemAt(2, QFormLayout::FieldRole)->setAlignment(Qt::AlignLeft);

    setContentLayout(formLayout);
    resizeToWidth(500);
    adjustAcceptedButton();
    nameLineEdit->setFocus();
}

QString NewProject::path() const {
    return directoryBrowseLineEdit->text() + "/" + nameLineEdit->text();
}

Project::Target NewProject::target() const {
    return static_cast<Project::Target>(targetComboBox->currentIndex());
}

void NewProject::adjustAcceptedButton() {
    setOkButtonEnabled(!nameLineEdit->text().isEmpty() && !directoryBrowseLineEdit->text().isEmpty());
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

    Global::project()->create(path(), target());
    StandardDialog::accept();
}

}
