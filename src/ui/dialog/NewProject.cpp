#include "NewProject.h"
#include "ui/component/BrowseLineEdit.h"
#include "ui/component/FormatComboBox.h"
#include "project/ProjectSettings.h"
#include "core/Settings.h"
#include <QtWidgets>

NewProject::NewProject() {
    setWindowTitle(tr("New Project"));

    nameLineEdit = new QLineEdit;
    connect(nameLineEdit, &QLineEdit::textChanged, this, &NewProject::adjustAcceptedButton);

    directoryBrowseLineEdit = new BrowseLineEdit(Settings::Project::workspace());
    connect(directoryBrowseLineEdit, &BrowseLineEdit::textChanged, this, &NewProject::adjustAcceptedButton);

    templateComboBox = new QComboBox;
    templateComboBox->addItem(tr("Binary"));
    templateComboBox->addItem(tr("Library"));

    formatComboBox = new FormatComboBox;

    auto formLayout = new QFormLayout;
    formLayout->addRow(new QLabel(tr("Name:")), nameLineEdit);
    formLayout->addRow(new QLabel(tr("Directory:")), directoryBrowseLineEdit);

    formLayout->addRow(new QLabel(tr("Template:")), templateComboBox);
    formLayout->itemAt(2, QFormLayout::FieldRole)->setAlignment(Qt::AlignLeft);

    formLayout->addRow(new QLabel(tr("Format:")), formatComboBox);
    formLayout->itemAt(3, QFormLayout::FieldRole)->setAlignment(Qt::AlignLeft);

    setContentLayout(formLayout);
    resizeToWidth(500);
    adjustAcceptedButton();
    nameLineEdit->setFocus();
}

QString NewProject::path() const {
    return directoryBrowseLineEdit->text() + "/" + nameLineEdit->text();
}

NormCommon::Project::Template NewProject::projectTemplate() const {
    return static_cast<NormCommon::Project::Template>(templateComboBox->currentIndex());
}

NormCommon::Project::Format NewProject::format() const {
    return formatComboBox->format();
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

    ProjectSettings settingsManager(path());
    settingsManager.create();
    settingsManager.setFormat(format());
    settingsManager.save();

    QFileInfo fi(path());
    QString filePath = path() + "/" + fi.baseName() + ".norm";

    NormCommon::Project project;
    project.create(projectTemplate());
    project.write(filePath, format());

    StandardDialog::accept();
}
