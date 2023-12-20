#pragma once
#include "core/async/Task.h"
#include "network/controller/project/Project.h"
#include <QWidget>

namespace Controller {
    class Project;
}

class QTableWidget;
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
    void edit();
    void deleteProject();

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

    Controller::Project* m_project = nullptr;
    QTableWidget* m_tableWidget = nullptr;
};
