#include "ProjectSettingsDialog.h"
#include "project/ProjectSettings.h"
#include "core/Global.h"
#include "ui/component/FormatComboBox.h"
#include <QtWidgets>

ProjectSettingsDialog::ProjectSettingsDialog() {
    setWindowTitle(tr("Project Settings"));

    formatComboBox = new FormatComboBox;
    formatComboBox->setFormat(Global::projectSettings()->format());

    auto formLayout = new QFormLayout;
    formLayout->addRow(tr("Format:"), formatComboBox);
    formLayout->itemAt(0, QFormLayout::FieldRole)->setAlignment(Qt::AlignLeft);

    setContentLayout(formLayout);
    resizeToWidth(600);
}

ProjectSettingsDialog::~ProjectSettingsDialog() {

}

void ProjectSettingsDialog::accept() {
    Global::projectSettings()->setFormat(formatComboBox->format());
    Global::projectSettings()->save();
    StandardDialog::accept();
}
