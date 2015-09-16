#include "projectdialog.h"
#include "../../settings.h"
#include <QtCore>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QDialogButtonBox>

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
