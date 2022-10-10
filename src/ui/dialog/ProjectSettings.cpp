#include "ProjectSettings.h"
#include "project/ProjectSettings.h"
#include "project/ProjectManager.h"
#include "core/Global.h"
#include "core/Constants.h"
#include "ui/component/SelectableLabel.h"
#include <QtWidgets>

namespace Dialog {

ProjectSettings::ProjectSettings() {
    setWindowTitle(tr("Project Settings"));

    QString target;

    if (Global::project()->target() == ProjectManager::Target::Application) {
        target = Const::Project::Target::Application::Name;
    } else if (Global::project()->target() == ProjectManager::Target::Library) {
        target = Const::Project::Target::Library::Name;
    } else {
        target = tr("Bad target");
    }

    auto formLayout = new QFormLayout;
    formLayout->addRow(tr("Path:"), new SelectableLabel(Global::project()->path()));
    formLayout->addRow(tr("Target:"), new SelectableLabel(target));
    formLayout->itemAt(1, QFormLayout::FieldRole)->setAlignment(Qt::AlignLeft);

    setContentLayout(formLayout);
    resizeToWidth(600);
}

ProjectSettings::~ProjectSettings() {

}

void ProjectSettings::accept() {
    Global::projectSettings()->save();
    StandardDialog::accept();
}

}
