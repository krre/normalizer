#include "NewProject.h"
#include "ui/widget/BrowseLayout.h"
#include <QLineEdit>
#include <QComboBox>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QMessageBox>
#include <QDir>

NewProject::NewProject(const QString& workDir) {
    setWindowTitle(tr("New Project"));

    m_nameLineEdit = new QLineEdit;
    connect(m_nameLineEdit, &QLineEdit::textChanged, this, &NewProject::setOkButtonState);

    m_directoryBrowseLayout = new BrowseLayout(workDir);
    connect(m_directoryBrowseLayout->lineEdit(), &QLineEdit::textChanged, this, &NewProject::setOkButtonState);

    m_targetComboBox = new QComboBox;
    m_targetComboBox->addItem(tr("Application"));
    m_targetComboBox->addItem(tr("Library"));

    auto formLayout = new QFormLayout;
    formLayout->addRow(tr("Name:"), m_nameLineEdit);
    formLayout->addRow(tr("Directory:"), m_directoryBrowseLayout);
    formLayout->addRow(tr("Target:"), m_targetComboBox);
    formLayout->itemAt(formLayout->indexOf(m_targetComboBox))->setAlignment(Qt::AlignLeft);

    setContentLayout(formLayout);

    resizeToWidth(500);
    m_nameLineEdit->setFocus();
    setOkButtonState();
}

QString NewProject::name() const {
    return m_nameLineEdit->text();
}

QString NewProject::directory() const {
    return m_directoryBrowseLayout->lineEdit()->text();
}

NewProject::Target NewProject::target() const {
    return static_cast<Target>(m_targetComboBox->currentIndex());
}

void NewProject::accept() {
    if (QDir().exists(directory() + "/" + name())) {
        QMessageBox::critical(this, QString(), tr("Project already exists!"));
    } else {
        StandardDialog::accept();
    }
}

void NewProject::setOkButtonState() {
    bool isAllFieldsFilled = !(m_nameLineEdit->text().isEmpty() || m_directoryBrowseLayout->lineEdit()->text().isEmpty());
    buttonBox()->button(QDialogButtonBox::Ok)->setEnabled(isAllFieldsFilled);
}
