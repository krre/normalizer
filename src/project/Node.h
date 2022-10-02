#pragma once
#include <QObject>

class Node : public QObject {
public:
    Node(Node* parent = nullptr);
};
