#include "ProjectTable.h"
#include "ProjectEditor.h"
#include <QtWidgets>

ProjectTable::ProjectTable() {
    auto toolBar = new QToolBar;

    toolBar->addAction(tr("Add"), this, &ProjectTable::addProject);
    toolBar->addAction(tr("Edit"), this, &ProjectTable::editProject);
    toolBar->addAction(tr("Delete"), this, &ProjectTable::deleteProject);

    m_tableWidget = new QTableWidget;
    m_tableWidget->setColumnCount(5);
    m_tableWidget->setHorizontalHeaderLabels({ tr("Name"), tr("Template"), tr("Description"), tr("Created time"), tr("Updated time") });
    m_tableWidget->setSelectionBehavior(QAbstractItemView::SelectItems);

    auto verticalLayout = new QVBoxLayout;
    verticalLayout->setContentsMargins(0, 0, 0, 0);
    verticalLayout->addWidget(toolBar);
    verticalLayout->addWidget(m_tableWidget);

    setLayout(verticalLayout);

    load();
}

void ProjectTable::addProject() {
    ProjectEditor projectEditor;
    projectEditor.exec();
}

void ProjectTable::editProject() {
    ProjectEditor projectEditor(1);
    projectEditor.exec();
}

void ProjectTable::deleteProject() {

}

void ProjectTable::load() {

}
