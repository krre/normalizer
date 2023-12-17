#include "ProjectTable.h"
#include "ProjectEditor.h"
#include "network/controller/project/Project.h"
#include <QtWidgets>

ProjectTable::ProjectTable(Controller::Project* project) : m_project(project) {
    m_tableWidget = new QTableWidget;
    m_tableWidget->setColumnCount(5);
    m_tableWidget->setHorizontalHeaderLabels({ tr("Name"), tr("Template"), tr("Description"), tr("Created time"), tr("Updated time") });
    m_tableWidget->setSelectionBehavior(QAbstractItemView::SelectItems);

    auto verticalLayout = new QVBoxLayout;
    verticalLayout->setContentsMargins(0, 0, 0, 0);
    verticalLayout->addWidget(m_tableWidget);

    setLayout(verticalLayout);
}

Async::Task<void> ProjectTable::load() {
    m_tableWidget->setRowCount(0);
    auto projects = co_await m_project->getList();
}

bool ProjectTable::isActive() const {
    return m_tableWidget->currentRow() >= 0;
}

void ProjectTable::add() {
    ProjectEditor projectEditor(m_project);
    projectEditor.exec();
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
