#pragma once
#include <QObject>
#include <QList>

class Node;
using Nodes = QList<Node*>;

class Node : public QObject {
public:
    Node(Node* parent = nullptr);
};
