#include "ProjectTable.h"
#include "ProjectEditor.h"
#include "ui/widget/TableWidget.h"
#include "core/Application.h"
#include <QtWidgets>

ProjectTable::ProjectTable(RestApi* restApi, Settings* settings) : m_settings(settings) {
    setWindowTitle(tr("Account Projects"));

    m_project.reset(new Controller::Project(restApi));

    QStringList columnLabels = { tr("Id"), tr("Name"), tr("Target"), tr("Description"), tr("Created time"), tr("Updated time") };

    m_tableWidget = new TableWidget;
    m_tableWidget->setColumnCount(columnLabels.count());
    m_tableWidget->setHorizontalHeaderLabels(columnLabels);
    m_tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    m_tableWidget->horizontalHeader()->restoreState(settings->projectTable().header);

    connect(m_tableWidget, &QTableWidget::itemSelectionChanged, this, [this] {
        emit currentRowChanged(currentRow());
    });

    connect(m_tableWidget, &QTableWidget::doubleClicked, this, &ProjectTable::open);
    connect(m_tableWidget, &QTableWidget::customContextMenuRequested, this, &ProjectTable::showContextMenu);

    auto verticalLayout = new QVBoxLayout;
    verticalLayout->setContentsMargins(QMargins());
    verticalLayout->addWidget(m_tableWidget);

    setLayout(verticalLayout);
    setAttribute(Qt::WA_DeleteOnClose);

    readSettings();
}

ProjectTable::~ProjectTable() {
    writeSettings();
}

Async::Task<void> ProjectTable::load() {
    m_tableWidget->setRowCount(0);
    auto projects = co_await m_project->getAll();

    for (const auto& project : projects) {
        addRow(project);
    }

    m_tableWidget->selectRow(0);
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
    emit openClicked(currentId().value(), m_tableWidget->item(currentRow().value(), int(Column::Name))->text());
}

Async::Task<void> ProjectTable::edit() {
    Id id = currentId().value();

    ProjectEditor projectEditor(m_project.data(), id);

    if (projectEditor.exec() == QDialog::Accepted) {
        Controller::Project::Response::Get project = co_await m_project->getOne(id);
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
    customMenu->exec(QCursor::pos());
}

void ProjectTable::showEvent(QShowEvent* event [[maybe_unused]]) {
    load();
}

void ProjectTable::readSettings() {
    QByteArray geometry = m_settings->projectTable().geometry;

    if (!geometry.isEmpty()) {
        restoreGeometry(geometry);
    } else {
        const QRect availableGeometry = QGuiApplication::screens().constFirst()->availableGeometry();
        resize(900, 500);
        move((availableGeometry.width() - width()) / 2, (availableGeometry.height() - height()) / 2);
    }
}

void ProjectTable::writeSettings() {
    Settings::ProjectTable projectTable;
    projectTable.geometry = saveGeometry();
    projectTable.header = m_tableWidget->horizontalHeader()->saveState();

    m_settings->setProjectTable(projectTable);
}

void ProjectTable::addRow(const Controller::Project::Response::Get& project) {
    m_tableWidget->insertRow(m_tableWidget->rowCount());
    int row = m_tableWidget->rowCount() - 1;

    QTableWidgetItem* idItem = new QTableWidgetItem(QString::number(project.id));
    m_tableWidget->setItem(row, int(Column::Id), idItem);

    QTableWidgetItem* nameItem = new QTableWidgetItem(project.name);
    m_tableWidget->setItem(row, int(Column::Name), nameItem);

    QTableWidgetItem* targetItem = new QTableWidgetItem(Project::targetString(project.target));
    m_tableWidget->setItem(row, int(Column::Target), targetItem);

    QTableWidgetItem* descriptionItem = new QTableWidgetItem(project.description);
    m_tableWidget->setItem(row, int(Column::Description), descriptionItem);

    QTableWidgetItem* createdItem = new QTableWidgetItem(project.createdTime.toString("yyyy.MM.dd hh:mm"));
    m_tableWidget->setItem(row, int(Column::CreatedTime), createdItem);

    QTableWidgetItem* updatedItem = new QTableWidgetItem(project.updatedTime.toString("yyyy.MM.dd hh:mm"));
    m_tableWidget->setItem(row, int(Column::UpdatedTime), updatedItem);
}

void ProjectTable::updateRow(const Controller::Project::Response::Get& project) {
    for (int i = 0; i < m_tableWidget->rowCount(); i++) {
        if (m_tableWidget->item(i, int(Column::Id))->text().toInt() == project.id) {
            m_tableWidget->item(i, int(Column::Name))->setText(project.name);
            m_tableWidget->item(i, int(Column::Description))->setText(project.description);
            m_tableWidget->item(i, int(Column::UpdatedTime))->setText(project.updatedTime.toString("yyyy.MM.dd hh:mm"));
            break;
        }
    }
}
