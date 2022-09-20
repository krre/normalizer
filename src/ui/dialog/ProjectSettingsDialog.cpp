#include "ProjectSettingsDialog.h"
#include "project/ProjectSettings.h"
#include "core/Global.h"
#include <QtWidgets>

ProjectSettingsDialog::ProjectSettingsDialog() {
    setWindowTitle(tr("Project Settings"));

    formatComboBox = new QComboBox;
    formatComboBox->addItem(tr("Binary"));
    formatComboBox->addItem(tr("Binary And JSON"));

    auto formLayout = new QFormLayout;
    formLayout->addRow(tr("Format:"), formatComboBox);
    formLayout->itemAt(0, QFormLayout::FieldRole)->setAlignment(Qt::AlignLeft);

    setContentLayout(formLayout);
    resizeToWidth(600);
}

ProjectSettingsDialog::~ProjectSettingsDialog() {

}

void ProjectSettingsDialog::accept() {
    Global::projectSettings()->setFormat(static_cast<ProjectSettings::Format>(formatComboBox->currentIndex()));
    Global::projectSettings()->save();
    StandardDialog::accept();
}
