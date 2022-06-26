#include "Workspace.h"
#include "core/Constants.h"
#include "core/Global.h"
#include <QtWidgets>

Workspace::Workspace(QWidget* parent) : StandardDialog(parent) {
    setWindowTitle(tr("Workspace"));

    lineEdit = new QLineEdit;
    auto browsePushButton = new QPushButton(tr("Browse..."));

    auto horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(lineEdit);
    horizontalLayout->addWidget(browsePushButton);

    auto verticalLayout = new QVBoxLayout;
    verticalLayout->addWidget(new QLabel(tr("Select directory for your Norm projects:")));
    verticalLayout->addLayout(horizontalLayout);

    setContentLayout(verticalLayout);
    resizeToWidth(430);

    connect(browsePushButton, &QPushButton::clicked, this, &Workspace::onBrowseButtonClicked);
    connect(lineEdit, &QLineEdit::textChanged, this, &Workspace::adjustAcceptedButton);

    lineEdit->setText(Global::workspacePath());
}

void Workspace::onBrowseButtonClicked() {
    QString dirPath = QFileDialog::getExistingDirectory(this);

    if (!dirPath.isEmpty()) {
        lineEdit->setText(dirPath);
    }
}

void Workspace::adjustAcceptedButton(const QString& text) {
    setOkButtonEnabled(!text.isEmpty());
}

void Workspace::accept() {
    QSettings settings;
    settings.setValue(Const::Settings::Project::Workspace, lineEdit->text());
    QDialog::accept();
}
