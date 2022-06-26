#include "Options.h"
#include "core/Constants.h"
#include "core/Global.h"
#include <QtWidgets>

Options::Options(QWidget* parent) : StandardDialog(parent) {
    setWindowTitle(tr("Options"));

    auto projectGroupBox = new QGroupBox(tr("Project"));
    workspaceLineEdit = new QLineEdit(projectGroupBox);

    auto workspacePushButton = new QPushButton(tr("Browse..."));
    connect(workspacePushButton, &QPushButton::clicked, this, &Options::onWorkspaceClicked);

    sessionCheckBox = new QCheckBox(tr("Restore session"));
    sessionCheckBox->setChecked(true);

    auto gridLayout = new QGridLayout(projectGroupBox);
    gridLayout->addWidget(new QLabel(tr("Workspace:")), 0, 0);
    gridLayout->addWidget(workspaceLineEdit, 0, 1);
    gridLayout->addWidget(workspacePushButton, 0, 2);
    gridLayout->addWidget(sessionCheckBox, 1, 0, -1, 0);

    auto verticalLayout = new QVBoxLayout;
    verticalLayout->addWidget(projectGroupBox);

    setContentLayout(verticalLayout);
    resizeToWidth(600);

    readSettings();
}

void Options::onWorkspaceClicked() {
    QFileInfo fi(workspaceLineEdit->text());
    QString dirPath = QFileDialog::getExistingDirectory(this, tr("Select Directory"), fi.dir().path());

    if (!dirPath.isEmpty()) {
        workspaceLineEdit->setText(dirPath);
    }
}

void Options::accept() {
    writeSettings();
    StandardDialog::accept();
}

void Options::readSettings() {
    QSettings settings;

    workspaceLineEdit->setText(Global::workspacePath());
    sessionCheckBox->setChecked(settings.value(Const::Settings::Session::Restore, Global::restoreSession()).toBool());
}

void Options::writeSettings() {
    QSettings settings;
    settings.setValue(Const::Settings::Project::Workspace, workspaceLineEdit->text());
    settings.setValue(Const::Settings::Session::Restore, sessionCheckBox->isChecked());

    QDir dir;
    dir.mkpath(workspaceLineEdit->text());
}
