#pragma once
#include <QtCore>
#include <QtQml>
#include "node.h"

class Scene : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<Node> nodes READ nodes)

public:
    explicit Scene(QObject *parent = 0);
    QQmlListProperty<Node> nodes();
    int count() const { return m_nodes.count(); }
    Node* node(int index) const { return m_nodes.at(index); }

private:
    QList<Node*> m_nodes;
};
