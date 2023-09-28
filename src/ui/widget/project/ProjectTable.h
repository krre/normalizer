#pragma once
#include <QTableWidget>

class QNetworkAccessManager;

class ProjectTable : public QTableWidget {
public:
    ProjectTable();

private:
    void load();

    QScopedPointer<QNetworkAccessManager> networkAccessManager;
};
