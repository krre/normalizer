#include "NodeTree.h"
#include "NodeTreeView.h"
#include "NodeProperties.h"
#include "ui/editor/NodeManager.h"
#include <QtWidgets>

NodeTree::NodeTree(NodeManager* nodeManager, QWidget* parent) : QWidget(parent) {
    m_treeView = new NodeTreeView(nodeManager);
    m_properties = new NodeProperties(nodeManager);

    m_splitter = new QSplitter;
    m_splitter->setHandleWidth(1);
    m_splitter->setChildrenCollapsible(false);
    m_splitter->setSizes({ 200, 500 });
    m_splitter->setContentsMargins(QMargins());

    m_splitter->addWidget(m_treeView);
    m_splitter->addWidget(m_properties);

    auto layout = new QVBoxLayout;
    layout->setContentsMargins(QMargins());
    layout->addWidget(m_splitter);

    setLayout(layout);
}
