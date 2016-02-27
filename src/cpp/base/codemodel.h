#pragma once
#include <QtCore>
#include "node.h"

class CodeModel : public QAbstractItemModel
{
    Q_OBJECT
    Q_PROPERTY(Node* rootNode READ rootNode CONSTANT)
public:
    explicit CodeModel(QObject *parent = 0);
    Q_INVOKABLE addNode(Node* parent, Node* node);

private:
    QModelIndex index(int row, int column, const QModelIndex& parent) const;
    QModelIndex parent(const QModelIndex& child) const;
    int rowCount(const QModelIndex& parent) const;
    int columnCount(const QModelIndex& parent) const;
    QVariant data(const QModelIndex& index, int role) const;
    Node* rootNode() { return &m_rootNode; }

    Node m_rootNode;
};
