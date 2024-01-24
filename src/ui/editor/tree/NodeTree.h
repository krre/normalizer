#pragma once
#include "core/CommonTypes.h"
#include <QWidget>

class NodeManager;
class NodeTreeView;
class NodeProperties;

class QSplitter;

class NodeTree : public QWidget {
public:
    explicit NodeTree(NodeManager* nodeManager, Id projectId, QWidget* parent = nullptr);

private:
    QSplitter* m_splitter = nullptr;

    NodeTreeView* m_treeView = nullptr;
    NodeProperties* m_properties = nullptr;
};
