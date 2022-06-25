#include "NewProject.h"
#include "core/Constants.h"
#include <QtWidgets>

NewProject::NewProject() {
    setWindowTitle(tr("New Project"));

    auto gridLayout = new QGridLayout;
    gridLayout->addWidget(new QLabel(tr("Name:")), 0, 0, 1, 1);
    gridLayout->addWidget(new QLabel(tr("Directory:")), 1, 0, 1, 1);

    nameLineEdit = new QLineEdit;
    gridLayout->addWidget(nameLineEdit, 0, 1, 1, 1);

    auto horizontalLayout = new QHBoxLayout;

    directoryLineEdit = new QLineEdit(QDir::homePath() + "/" + Const::Norm::Name);
    horizontalLayout->addWidget(directoryLineEdit);

    auto browsePushButton = new QPushButton(tr("Browse..."));
    horizontalLayout->addWidget(browsePushButton);

    gridLayout->addLayout(horizontalLayout, 1, 1, 1, 1);
    gridLayout->addWidget(new QLabel(tr("Template:")), 2, 0, 1, 1);

    templateComboBox = new QComboBox;
    templateComboBox->addItem(tr("Binary"));
    templateComboBox->addItem(tr("Library"));

    gridLayout->addWidget(templateComboBox, 2, 1, 1, 1, Qt::AlignLeft);

    setContentLayout(gridLayout);
    resizeToWidth(400);

    connect(browsePushButton, &QPushButton::clicked, this, &NewProject::onBrowseButtonClicked);
    connect(nameLineEdit, &QLineEdit::textChanged, this, &NewProject::adjustAcceptedButton);
    connect(directoryLineEdit, &QLineEdit::textChanged, this, &NewProject::adjustAcceptedButton);

    adjustAcceptedButton();
    nameLineEdit->setFocus();
}

QString NewProject::path() const {
    QString result = directoryLineEdit->text() + "/" + nameLineEdit->text();

    if (result.last(QString(Const::Norm::Extension).count()) != Const::Norm::Extension) {
        result += Const::Norm::Extension;
    }

    return result;
}

void NewProject::onBrowseButtonClicked() {
    QString dirPath = QFileDialog::getExistingDirectory(this);

    if (!dirPath.isEmpty()) {
        directoryLineEdit->setText(dirPath);
    }
}

void NewProject::adjustAcceptedButton() {
    setOkButtonEnabled(!nameLineEdit->text().isEmpty() && !directoryLineEdit->text().isEmpty());
}
