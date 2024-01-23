#include "ProjectTable.h"
#include "ProjectEditor.h"
#include "ui/widget/TableWidget.h"
#include "core/Application.h"
#include <QtWidgets>

ProjectTable::ProjectTable(RestApi* restApi) {
    m_project.reset(new Controller::Project(restApi));

    QStringList columnLabels = { tr("Id"), tr("Name"), tr("Target"), tr("Description"), tr("Created time"), tr("Updated time") };

    m_tableWidget = new TableWidget;
    m_tableWidget->setColumnCount(columnLabels.count());
    m_tableWidget->setHorizontalHeaderLabels(columnLabels);
    m_tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(m_tableWidget, &QTableWidget::itemSelectionChanged, this, [this] {
        emit currentRowChanged(currentRow());
    });

    connect(m_tableWidget, &QTableWidget::doubleClicked, this, &ProjectTable::open);
    connect(m_tableWidget, &QTableWidget::customContextMenuRequested, this, &ProjectTable::showContextMenu);

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

std::optional<int> ProjectTable::currentRow() const {
    if (m_tableWidget->selectedItems().count()) {
        return m_tableWidget->selectedItems().first()->row();
    }

    return {};
}

std::optional<Id> ProjectTable::currentId() const {
    auto row = currentRow();

    if (row.has_value()) {
        return m_tableWidget->item(row.value(), int(Column::Id))->text().toInt();
    }

    return {};
}

void ProjectTable::create() {
    ProjectEditor projectEditor(m_project.data());

    if (projectEditor.exec() == QDialog::Accepted) {
        load();
    }
}

void ProjectTable::open() {
    emit opened(currentId().value(), m_tableWidget->item(currentRow().value(), int(Column::Name))->text());
}

Async::Task<void> ProjectTable::edit() {
    Id id = currentId().value();

    ProjectEditor projectEditor(m_project.data(), id);

    if (projectEditor.exec() == QDialog::Accepted) {
        Controller::Project::GetResponse project = co_await m_project->getOne(id);
        updateRow(project);
    }
}

Async::Task<void> ProjectTable::remove() {
    if (QMessageBox::warning(this, Application::Name,
                            tr("Delete the project?"),
                            QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Cancel) != QMessageBox::Ok) {
        co_return;
    }

    Id id = currentId().value();
    co_await m_project->remove(id);

    for (int i = 0; i < m_tableWidget->rowCount(); i++) {
        if (m_tableWidget->item(i, int(Column::Id))->text().toInt() == id) {
            m_tableWidget->removeRow(i);
            break;
        }
    }
}

void ProjectTable::showContextMenu(const QPoint& pos) {
    auto index = m_tableWidget->indexAt(pos);

    if (!index.isValid()) return;

    auto customMenu = new QMenu(m_tableWidget);
    customMenu->addAction(tr("Open"), this, &ProjectTable::open);
    customMenu->addAction(tr("Edit..."), this, &ProjectTable::edit);
    customMenu->addAction(tr("Delete..."), this, &ProjectTable::remove);
    customMenu->exec(m_tableWidget->mapToGlobal(pos));
}

void ProjectTable::showEvent(QShowEvent* event [[maybe_unused]]) {
    load();
}

void ProjectTable::addRow(const Controller::Project::GetResponse& project) {
    m_tableWidget->insertRow(m_tableWidget->rowCount());
    int row = m_tableWidget->rowCount() - 1;

    QTableWidgetItem* idItem = new QTableWidgetItem(QString::number(project.id));
    m_tableWidget->setItem(row, int(Column::Id), idItem);

    QTableWidgetItem* nameItem = new QTableWidgetItem(project.name);
    m_tableWidget->setItem(row, int(Column::Name), nameItem);

    QTableWidgetItem* targetItem = new QTableWidgetItem(Controller::Project::targetString(project.target));
    m_tableWidget->setItem(row, int(Column::Target), targetItem);

    QTableWidgetItem* descriptionItem = new QTableWidgetItem(project.description);
    m_tableWidget->setItem(row, int(Column::Description), descriptionItem);

    QTableWidgetItem* createdItem = new QTableWidgetItem(project.createdTime.toString("yyyy.MM.dd hh:mm"));
    m_tableWidget->setItem(row, int(Column::CreatedTime), createdItem);

    QTableWidgetItem* updatedItem = new QTableWidgetItem(project.updatedTime.toString("yyyy.MM.dd hh:mm"));
    m_tableWidget->setItem(row, int(Column::UpdatedTime), updatedItem);
}

void ProjectTable::updateRow(const Controller::Project::GetResponse& project) {
    for (int i = 0; i < m_tableWidget->rowCount(); i++) {
        if (m_tableWidget->item(i, int(Column::Id))->text().toInt() == project.id) {
            m_tableWidget->item(i, int(Column::Name))->setText(project.name);
            m_tableWidget->item(i, int(Column::Description))->setText(project.description);
            m_tableWidget->item(i, int(Column::UpdatedTime))->setText(project.updatedTime.toString("yyyy.MM.dd hh:mm"));
            break;
        }
    }
}
