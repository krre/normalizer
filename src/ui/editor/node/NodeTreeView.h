#pragma once
#include <QTreeView>

class NodeTreeView : public QTreeView {
public:
    NodeTreeView();

private slots:
    void showContextMenu(const QPoint& point);
    void addModule();
};
