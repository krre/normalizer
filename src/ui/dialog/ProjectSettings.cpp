#include "ProjectSettings.h"
#include "ui/component/FormatComboBox.h"
#include <QtWidgets>

ProjectSettings::ProjectSettings() {
    setWindowTitle(tr("Project Settings"));

    formatComboBox = new FormatComboBox;

    auto formLayout = new QFormLayout;
    formLayout->addRow(tr("Format:"), formatComboBox);
    formLayout->itemAt(0, QFormLayout::FieldRole)->setAlignment(Qt::AlignLeft);

    setContentLayout(formLayout);
    resizeToWidth(600);
}

void ProjectSettings::accept() {
    StandardDialog::accept();
}
