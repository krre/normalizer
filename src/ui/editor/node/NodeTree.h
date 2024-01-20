#pragma once
#include <QWidget>

class NodeTreeView;
class NodeProperties;

class QSplitter;

class NodeTree : public QWidget {
public:
    explicit NodeTree(QWidget* parent = nullptr);

private:
    QSplitter* m_splitter = nullptr;

    NodeTreeView* m_treeView = nullptr;
    NodeProperties* m_properties = nullptr;
};
