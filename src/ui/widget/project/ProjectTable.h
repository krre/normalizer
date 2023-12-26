#pragma once
#include "core/async/Task.h"
#include "network/controller/project/Project.h"
#include <QWidget>

class TableWidget;

namespace Controller {
    class Project;
}

class QNetworkAccessManager;

class ProjectTable : public QWidget {
    Q_OBJECT
public:
    ProjectTable(Controller::Project* project);

    std::optional<int> currentRow() const;
    std::optional<Id> currentId() const;
    Async::Task<void> load();

signals:
    void currentRowChanged(std::optional<int> row);
    void opened(Id id);

public slots:
    void create();
    void open();
    Async::Task<void> edit();
    Async::Task<void> deleteProject();

    void showContextMenu(const QPoint& pos);

protected:
    void showEvent(QShowEvent* event) override;

private:
    enum class Column {
        Id,
        Name,
        Template,
        Description,
        CreatedTime,
        UpdatedTime,
    };

    void addRow(const Controller::Project::GetProject& project);
    void updateRow(const Controller::Project::GetProject& project);

    Controller::Project* m_project = nullptr;
    TableWidget* m_tableWidget = nullptr;
};
