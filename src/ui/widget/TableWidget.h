#pragma once
#include <QTableWidget>

class TableWidget : public QTableWidget {
public:
    TableWidget();

protected:
    void mousePressEvent(QMouseEvent* event) override;
};
