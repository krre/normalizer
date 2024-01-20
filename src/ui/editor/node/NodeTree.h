#pragma once
#include <QWidget>

class NodeModel;
class NodeTreeView;
class NodeProperties;

class QSplitter;

class NodeTree : public QWidget {
public:
    explicit NodeTree(NodeModel* model, QWidget* parent = nullptr);

private:
    QSplitter* m_splitter = nullptr;

    NodeTreeView* m_treeView = nullptr;
    NodeProperties* m_properties = nullptr;
};
