#include "NewWorkspace.h"
#include <QLineEdit>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QMessageBox>

NewWorkspace::NewWorkspace() {
    setWindowTitle(tr("New Workspace"));

    m_nameLineEdit = new QLineEdit;
    connect(m_nameLineEdit, &QLineEdit::textChanged, this, &NewWorkspace::setOkButtonState);

    auto formLayout = new QFormLayout;
    formLayout->addRow(tr("Name:"), m_nameLineEdit);

    setContentLayout(formLayout);

    resizeToWidth(500);
    m_nameLineEdit->setFocus();
    setOkButtonState();
}

QString NewWorkspace::name() const {
    return m_nameLineEdit->text();
}

void NewWorkspace::accept() {
    StandardDialog::accept();
}

void NewWorkspace::setOkButtonState() {
    buttonBox()->button(QDialogButtonBox::Ok)->setEnabled(!m_nameLineEdit->text().isEmpty());
}
