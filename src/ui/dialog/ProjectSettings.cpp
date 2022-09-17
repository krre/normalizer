#include "ProjectSettings.h"

ProjectSettings::ProjectSettings() {
    setWindowTitle(tr("Project Settings"));

    resizeToWidth(600);
}

void ProjectSettings::accept() {
    StandardDialog::accept();
}
