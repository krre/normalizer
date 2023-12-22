#include "ProjectTable.h"
#include "ProjectEditor.h"
#include "ui/widget/TableWidget.h"
#include <QtWidgets>

ProjectTable::ProjectTable(Controller::Project* project) : m_project(project) {
    QStringList columnLabels = { tr("Id"), tr("Name"), tr("Template"), tr("Description"), tr("Created time"), tr("Updated time") };

    m_tableWidget = new TableWidget;
    m_tableWidget->setColumnCount(columnLabels.count());
    m_tableWidget->setHorizontalHeaderLabels(columnLabels);

    connect(m_tableWidget, &QTableWidget::itemSelectionChanged, this, [this] {
        emit currentRowChanged(currentRow());
    });

    connect(m_tableWidget, &QTableWidget::doubleClicked, this, &ProjectTable::edit);

    auto verticalLayout = new QVBoxLayout;
    verticalLayout->setContentsMargins(0, 0, 0, 0);
    verticalLayout->addWidget(m_tableWidget);

    setLayout(verticalLayout);
}

Async::Task<void> ProjectTable::load() {
    m_tableWidget->setRowCount(0);
    auto projects = co_await m_project->getAll();

    for (const auto& project : projects) {
        addRow(project);
    }

    m_tableWidget->selectRow(0);
    m_tableWidget->resizeColumnsToContents();
}

bool ProjectTable::isActive() const {
    return m_tableWidget->currentRow() >= 0;
}

int ProjectTable::currentRow() const {
    return m_tableWidget->selectedItems().count() ? m_tableWidget->selectedItems().first()->row() : -1;
}

void ProjectTable::add() {
    ProjectEditor projectEditor(m_project);

    if (projectEditor.exec() == QDialog::Accepted) {
        load();
    }
}

Async::Task<void> ProjectTable::edit() {
    Id id = m_tableWidget->item(currentRow(), int(Column::Id))->text().toInt();

    ProjectEditor projectEditor(m_project, id);

    if (projectEditor.exec() == QDialog::Accepted) {
        Controller::Project::GetProject project = co_await m_project->getOne(id);
        updateRow(project);
    }
}

Async::Task<void> ProjectTable::deleteProject() {
    if (QMessageBox::warning(this,
                             tr("Confirm Deleting Project"),
                             tr("Delete the project?"),
                             QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Cancel) != QMessageBox::Ok) {
        co_return;
    }

    Id id = m_tableWidget->item(currentRow(), int(Column::Id))->text().toInt();
    co_await m_project->remove(id);

    for (int i = 0; i < m_tableWidget->rowCount(); i++) {
        if (m_tableWidget->item(i, int(Column::Id))->text().toInt() == id) {
            m_tableWidget->removeRow(i);
            break;
        }
    }
}

void ProjectTable::showEvent(QShowEvent* event [[maybe_unused]]) {
    load();
}

void ProjectTable::addRow(const Controller::Project::GetProject& project) {
    m_tableWidget->insertRow(m_tableWidget->rowCount());
    int row = m_tableWidget->rowCount() - 1;

    QTableWidgetItem* idItem = new QTableWidgetItem(QString::number(project.id));
    m_tableWidget->setItem(row, int(Column::Id), idItem);

    QTableWidgetItem* nameItem = new QTableWidgetItem(project.name);
    m_tableWidget->setItem(row, int(Column::Name), nameItem);

    QTableWidgetItem* templateItem = new QTableWidgetItem(Controller::Project::templateToString(project.projectTemplate));
    m_tableWidget->setItem(row, int(Column::Template), templateItem);

    QTableWidgetItem* descriptionItem = new QTableWidgetItem(project.description);
    m_tableWidget->setItem(row, int(Column::Description), descriptionItem);

    QTableWidgetItem* createdItem = new QTableWidgetItem(project.createdTime.toString("yyyy.MM.dd hh:mm"));
    m_tableWidget->setItem(row, int(Column::CreatedTime), createdItem);

    QTableWidgetItem* updatedItem = new QTableWidgetItem(project.updatedTime.toString("yyyy.MM.dd hh:mm"));
    m_tableWidget->setItem(row, int(Column::UpdatedTime), updatedItem);
}

void ProjectTable::updateRow(const Controller::Project::GetProject& project) {
    for (int i = 0; i < m_tableWidget->rowCount(); i++) {
        if (m_tableWidget->item(i, int(Column::Id))->text().toInt() == project.id) {
            m_tableWidget->item(i, int(Column::Name))->setText(project.name);
            m_tableWidget->item(i, int(Column::Description))->setText(project.description);
            m_tableWidget->item(i, int(Column::UpdatedTime))->setText(project.updatedTime.toString("yyyy.MM.dd hh:mm"));
            break;
        }
    }
}
