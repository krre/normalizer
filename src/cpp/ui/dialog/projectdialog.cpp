#include "projectdialog.h"
#include "../../settings.h"
#include <QtCore>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QFileDialog>

extern QSharedPointer<Settings> settings;

ProjectDialog::ProjectDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle(tr("New Project"));
    setAttribute(Qt::WA_DeleteOnClose );
    resize(500, 100);

    QGridLayout* layout = new QGridLayout(this);

    QLabel* nameLabel = new QLabel(tr("Name:"));
    QLineEdit* nameLineEdit = new QLineEdit("project");
    layout->addWidget(nameLabel, 0, 0);
    layout->addWidget(nameLineEdit, 0, 1, 1, 2);

    QLabel* directoryLabel = new QLabel(tr("Directory:"));
    QString projectDir = settings.data()->getRecentDirectory();
    if (projectDir.isEmpty()) {
        projectDir = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    }
    directoryLineEdit = new QLineEdit(projectDir);
    QPushButton* browseButton = new QPushButton(tr("Browse..."));
    connect(browseButton, SIGNAL(clicked(bool)), this, SLOT(onBrowseDirectory()));
    layout->addWidget(directoryLabel, 1, 0);
    layout->addWidget(directoryLineEdit, 1, 1);
    layout->addWidget(browseButton, 1, 2);

    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(onAccepted()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    layout->addWidget(buttonBox, 2, 0, 1, 2);
}

void ProjectDialog::onAccepted()
{
    settings.data()->setRecentDirectory(directoryLineEdit->text());
    accept();
}

void ProjectDialog::onBrowseDirectory()
{
    QFileDialog::Options options = QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly;
    QString directory = QFileDialog::getExistingDirectory(this,
                                tr("Select Directory"),
                                directoryLineEdit->text(),
                                options);
    if (!directory.isEmpty()) {
        directoryLineEdit->setText(directory);
    }
}
