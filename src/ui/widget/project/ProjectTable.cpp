#include "ProjectTable.h"
#include "ProjectEditor.h"
#include <QtWidgets>

ProjectTable::ProjectTable(Controller::Project* project) : m_project(project) {
    QStringList columnLabels = { tr("Id"), tr("Name"), tr("Template"), tr("Description"), tr("Created time"), tr("Updated time") };

    m_tableWidget = new QTableWidget;
    m_tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_tableWidget->setColumnCount(columnLabels.count());
    m_tableWidget->setHorizontalHeaderLabels(columnLabels);

    connect(m_tableWidget, &QTableWidget::itemSelectionChanged, this, [this] {
        emit currentRowChanged(currentRow());
    });

    auto verticalLayout = new QVBoxLayout;
    verticalLayout->setContentsMargins(0, 0, 0, 0);
    verticalLayout->addWidget(m_tableWidget);

    setLayout(verticalLayout);
}

Async::Task<void> ProjectTable::load() {
    m_tableWidget->setRowCount(0);
    auto projects = co_await m_project->getList();

    for (const auto& project : projects) {
        addRow(project);
    }

    m_tableWidget->selectRow(0);
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

void ProjectTable::edit() {
    ProjectEditor projectEditor(m_project, 1);
    projectEditor.exec();
}

void ProjectTable::deleteProject() {

}

void ProjectTable::showEvent(QShowEvent* event [[maybe_unused]]) {
    load();
}

void ProjectTable::addRow(const Controller::Project::GetProject& project) {
    m_tableWidget->insertRow(m_tableWidget->rowCount());

    QTableWidgetItem* idItem = new QTableWidgetItem(QString::number(project.id));
    m_tableWidget->setItem(m_tableWidget->rowCount() - 1, int(Column::Id), idItem);

    QTableWidgetItem* nameItem = new QTableWidgetItem(project.name);
    m_tableWidget->setItem(m_tableWidget->rowCount() - 1, int(Column::Name), nameItem);

    QTableWidgetItem* templateItem = new QTableWidgetItem(Controller::Project::templateToString(project.projectTemplate));
    m_tableWidget->setItem(m_tableWidget->rowCount() - 1, int(Column::Template), templateItem);

    QTableWidgetItem* descriptionItem = new QTableWidgetItem(project.description);
    m_tableWidget->setItem(m_tableWidget->rowCount() - 1, int(Column::Description), descriptionItem);

    QTableWidgetItem* createdItem = new QTableWidgetItem(project.createdTime.toString("yyyy.MM.dd hh:mm"));
    m_tableWidget->setItem(m_tableWidget->rowCount() - 1, int(Column::CreatedTime), createdItem);

    QTableWidgetItem* updatedItem = new QTableWidgetItem(project.updatedTime.toString("yyyy.MM.dd hh:mm"));
    m_tableWidget->setItem(m_tableWidget->rowCount() - 1, int(Column::UpdatedTime), updatedItem);
}
