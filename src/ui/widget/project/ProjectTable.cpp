#include "ProjectTable.h"
#include "ProjectEditor.h"
#include <QtWidgets>

ProjectTable::ProjectTable() {
    m_tableWidget = new QTableWidget;
    m_tableWidget->setColumnCount(5);
    m_tableWidget->setHorizontalHeaderLabels({ tr("Name"), tr("Template"), tr("Description"), tr("Created time"), tr("Updated time") });
    m_tableWidget->setSelectionBehavior(QAbstractItemView::SelectItems);

    auto verticalLayout = new QVBoxLayout;
    verticalLayout->setContentsMargins(0, 0, 0, 0);
    verticalLayout->addWidget(m_tableWidget);

    setLayout(verticalLayout);

    load();
}

bool ProjectTable::isActive() const {
    return m_tableWidget->currentRow() >= 0;
}

void ProjectTable::add() {
    ProjectEditor projectEditor;
    projectEditor.exec();
}

void ProjectTable::edit() {
    ProjectEditor projectEditor(1);
    projectEditor.exec();
}

void ProjectTable::deleteProject() {

}

void ProjectTable::load() {

}
