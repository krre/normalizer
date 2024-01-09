#include "NodeTree.h"
#include "NodeTreeWidget.h"
#include "NodeProperties.h"
#include <QtWidgets>

NodeTree::NodeTree(QWidget* parent) : QWidget(parent) {
    m_treeWidget = new NodeTreeWidget;
    m_properties = new NodeProperties;

    m_splitter = new QSplitter;
    m_splitter->setHandleWidth(1);
    m_splitter->setChildrenCollapsible(false);
    m_splitter->setSizes({ 200, 500 });
    m_splitter->setContentsMargins(QMargins());

    m_splitter->addWidget(m_treeWidget);
    m_splitter->addWidget(m_properties);

    auto layout = new QVBoxLayout;
    layout->setContentsMargins(QMargins());
    layout->addWidget(m_splitter);

    setLayout(layout);
}
