#include "Workspace.h"
#include "core/Settings.h"
#include "ui/component/BrowseLineEdit.h"
#include <QtWidgets>

namespace Dialog {

Workspace::Workspace(QWidget* parent) : StandardDialog(parent) {
    setWindowTitle(tr("Workspace"));

    workspaceBrowseLineEdit = new BrowseLineEdit(Settings::Project::workspace());
    connect(workspaceBrowseLineEdit, &BrowseLineEdit::textChanged, this, &Workspace::adjustAcceptedButton);

    auto verticalLayout = new QVBoxLayout;
    verticalLayout->addWidget(new QLabel(tr("Directory for Norm projects:")));
    verticalLayout->addLayout(workspaceBrowseLineEdit);

    setContentLayout(verticalLayout);
    resizeToWidth(430);
}

void Workspace::adjustAcceptedButton(const QString& text) {
    setOkButtonEnabled(!text.isEmpty());
}

void Workspace::accept() {
    Settings::Project::setWorkspace(workspaceBrowseLineEdit->text());

    QDir dir;
    dir.mkpath(workspaceBrowseLineEdit->text());

    QDialog::accept();
}

}
