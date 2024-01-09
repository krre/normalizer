#pragma once
#include <QTreeWidget>

class NodeTreeWidget : public QTreeWidget {
public:
    NodeTreeWidget();

private slots:
    void showContextMenu(const QPoint& point);
};
