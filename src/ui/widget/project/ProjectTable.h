#pragma once
#include <QWidget>

class QTableWidget;
class QNetworkAccessManager;

class ProjectTable : public QWidget {
public:
    ProjectTable();

private:
    void addProject();
    void editProject();
    void deleteProject();

private:
    void load();

    QTableWidget* m_tableWidget = nullptr;
};
