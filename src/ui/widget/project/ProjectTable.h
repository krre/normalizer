#pragma once
#include <QWidget>

class QTableWidget;
class QNetworkAccessManager;

class ProjectTable : public QWidget {
public:
    ProjectTable();

    bool isActive() const;

public slots:
    void add();
    void edit();
    void deleteProject();

private:
    void load();

    QTableWidget* m_tableWidget = nullptr;
};
