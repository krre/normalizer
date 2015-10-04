#include "node.h"

Node::Node(QObject *parent) : QObject(parent)
{

}

QQmlListProperty<Node> Node::nodes()
{
    return QQmlListProperty<Node>(this, 0, Node::appendNode, Node::nodeCount, Node::nodeAt, Node::clearNode);
}

void Node::appendNode(QQmlListProperty<Node>* list, Node *node)
{
    if (!node) {
        return;
    }
    Node* self = static_cast<Node*>(list->object);
    self->m_nodes.append(node);
    self->nodesChanged();
}

Node* Node::nodeAt(QQmlListProperty<Node>* list, int index)
{
    Node* self = static_cast<Node*>(list->object);
    return self->m_nodes.at(index);
}

int Node::nodeCount(QQmlListProperty<Node>* list)
{
    Node* self = static_cast<Node*>(list->object);
    return self->m_nodes.count();
}

void Node::clearNode(QQmlListProperty<Node>* list)
{
    Node* self = static_cast<Node*>(list->object);
    self->m_nodes.clear();
    self->nodesChanged();
}


void Node::setPosition(QVector3D position)
{
    if (m_position == position)
        return;

    m_position = position;
    emit positionChanged(position);
}

void Node::setRotation(QVector3D rotation)
{
    if (m_rotation == rotation)
        return;

    m_rotation = rotation;
    emit rotationChanged(rotation);
}

void Node::setScale(QVector3D scale)
{
    if (m_scale == scale)
        return;

    m_scale = scale;
    emit scaleChanged(scale);
}

