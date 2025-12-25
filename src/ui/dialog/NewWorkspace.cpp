#include "NewWorkspace.h"
#include "network/api/common/Workspace.h"
#include <QLineEdit>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QMessageBox>

NewWorkspace::NewWorkspace(Network* network) : m_network(network) {
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
    createWorkspace();
}

void NewWorkspace::setOkButtonState() {
    buttonBox()->button(QDialogButtonBox::Ok)->setEnabled(!m_nameLineEdit->text().isEmpty());
}

Async::Task<void> NewWorkspace::createWorkspace() {
    Api::Workspace workspace(m_network);
    Api::Id id = co_await workspace.create(m_nameLineEdit->text());
    qDebug() << id;

    StandardDialog::accept();
    co_return;
}
