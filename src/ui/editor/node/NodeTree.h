#pragma once
#include <QWidget>

class NodeTreeWidget;
class NodeProperties;

class QSplitter;

class NodeTree : public QWidget {
public:
    explicit NodeTree(QWidget* parent = nullptr);

private:
    QSplitter* m_splitter = nullptr;

    NodeTreeWidget* m_treeWidget = nullptr;
    NodeProperties* m_properties = nullptr;
};
