#pragma once
#include "core/async/Task.h"
#include "external/network/controller/project/Project.h"
#include <QWidget>

class RestApi;
class TableWidget;

class QNetworkAccessManager;

class ProjectTable : public QWidget {
    Q_OBJECT
public:
    ProjectTable(RestApi* restApi);

    std::optional<int> currentRow() const;
    std::optional<Id> currentId() const;
    Async::Task<void> load();

signals:
    void currentRowChanged(std::optional<int> row);
    void opened(Id id, const QString& name);

public slots:
    void create();
    void open();
    Async::Task<void> edit();
    Async::Task<void> remove();

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

    void addRow(const Controller::Project::GetParams& project);
    void updateRow(const Controller::Project::GetParams& project);

    QScopedPointer<Controller::Project> m_project;
    TableWidget* m_tableWidget = nullptr;
};
