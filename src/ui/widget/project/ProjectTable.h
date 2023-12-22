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

    bool isActive() const;
    int currentRow() const;
    Async::Task<void> load();

signals:
    void currentRowChanged(int row);

public slots:
    void add();
    Async::Task<void> edit();
    Async::Task<void> deleteProject();

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
