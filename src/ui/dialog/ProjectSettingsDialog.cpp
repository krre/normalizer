#include "ProjectSettingsDialog.h"
#include "project/ProjectSettings.h"
#include "core/Global.h"
#include "core/Constants.h"
#include "ui/component/SelectableLabel.h"
#include <QtWidgets>

ProjectSettingsDialog::ProjectSettingsDialog() {
    setWindowTitle(tr("Project Settings"));

    QString target;

    if (Global::project()->target() == NormCommon::Project::Target::Application) {
        target = Const::Project::Target::Application;
    } else if (Global::project()->target() == NormCommon::Project::Target::Library) {
        target = Const::Project::Target::Library;
    } else {
        target = tr("Bad target");
    }

    formatComboBox = new QComboBox;
    formatComboBox->addItem(tr("Binary"));
    formatComboBox->addItem(tr("Binary And JSON"));

    auto formLayout = new QFormLayout;
    formLayout->addRow(tr("Path:"), new SelectableLabel(Global::project()->path()));
    formLayout->addRow(tr("Target:"), new SelectableLabel(target));
    formLayout->addRow(tr("Format:"), formatComboBox);
    formLayout->itemAt(2, QFormLayout::FieldRole)->setAlignment(Qt::AlignLeft);

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
