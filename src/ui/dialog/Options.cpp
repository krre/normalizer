#include "Options.h"
#include "ui/component/BrowseLineEdit.h"
#include "core/Settings.h"
#include <QtWidgets>

namespace Dialog {

Options::Options(QWidget* parent) : StandardDialog(parent) {
    setWindowTitle(tr("Options"));

    auto projectGroupBox = new QGroupBox(tr("Project"));

    workspaceBrowseLineEdit = new BrowseLineEdit;
    openLastProjectCheckBox = new QCheckBox(tr("Open last project"));
    sessionCheckBox = new QCheckBox(tr("Restore session"));

    auto formLayout = new QFormLayout(projectGroupBox);
    formLayout->addRow(new QLabel(tr("Workspace:")), workspaceBrowseLineEdit);
    formLayout->addRow(openLastProjectCheckBox);
    formLayout->addRow(sessionCheckBox);

    auto verticalLayout = new QVBoxLayout;
    verticalLayout->addWidget(projectGroupBox);

    setContentLayout(verticalLayout);
    resizeToWidth(600);

    readSettings();
}

void Options::accept() {
    writeSettings();
    StandardDialog::accept();
}

void Options::readSettings() {
    workspaceBrowseLineEdit->setText(Settings::Project::workspace());
    openLastProjectCheckBox->setChecked(Settings::Project::openLast());
    sessionCheckBox->setChecked(Settings::Project::restoreSession());
}

void Options::writeSettings() {
    Settings::Project::setWorkspace(workspaceBrowseLineEdit->text());
    Settings::Project::setOpenLast(openLastProjectCheckBox->isChecked());
    Settings::Project::setRestoreSession(sessionCheckBox->isChecked());

    QDir dir;
    dir.mkpath(workspaceBrowseLineEdit->text());
}

}
