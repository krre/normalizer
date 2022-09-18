#include "ProjectSettingsDialog.h"
#include "project/ProjectSettings.h"
#include "ui/component/FormatComboBox.h"
#include <QtWidgets>

ProjectSettingsDialog::ProjectSettingsDialog(const QString& projectPath) {
    setWindowTitle(tr("Project Settings"));

    settings.reset(new ProjectSettings(projectPath));
    settings->load();

    formatComboBox = new FormatComboBox;
    formatComboBox->setFormat(settings->format());

    auto formLayout = new QFormLayout;
    formLayout->addRow(tr("Format:"), formatComboBox);
    formLayout->itemAt(0, QFormLayout::FieldRole)->setAlignment(Qt::AlignLeft);

    setContentLayout(formLayout);
    resizeToWidth(600);
}

ProjectSettingsDialog::~ProjectSettingsDialog() {

}

void ProjectSettingsDialog::accept() {
    settings->setFormat(formatComboBox->format());
    settings->save();
    StandardDialog::accept();
}
