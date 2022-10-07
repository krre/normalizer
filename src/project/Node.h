#pragma once
#include <QObject>
#include <QList>

class Node;
using Nodes = QList<Node*>;

class Node : public QObject {
public:
    using Id = qint64;
    Node(Node* parent = nullptr);

    Id id() const;
    void setId(Id id);

private:
    Id m_id = 0;
};
