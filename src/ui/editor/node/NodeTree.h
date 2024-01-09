#pragma once
#include <QWidget>

class NodeProperties;
class QTreeWidget;
class QSplitter;

class NodeTree : public QWidget {
public:
    explicit NodeTree(QWidget* parent = nullptr);

private:
    QSplitter* m_splitter = nullptr;
    QTreeWidget* m_treeWidget = nullptr;
    NodeProperties* m_properties = nullptr;
};
