#include "NodeProperties.h"

NodeProperties::NodeProperties(NodeManager* nodeManager, QWidget* parent) : QWidget(parent),m_nodeManager(nodeManager) {
    setMinimumWidth(100);
}
