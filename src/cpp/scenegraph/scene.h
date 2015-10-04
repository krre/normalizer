#pragma once
#include <QtCore>
#include <QtQml>
#include "node.h"

class Scene : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<Node> nodes READ nodes)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_CLASSINFO("DefaultProperty", "nodes")

public:
    explicit Scene(QObject *parent = 0);
    QQmlListProperty<Node> nodes() { return QQmlListProperty<Node>(this, m_nodes); }
    int count() const { return m_nodes.count(); }
    Node* node(int index) const { return m_nodes.at(index); }

    QColor color() const { return m_color; }
    void setColor(QColor color);

signals:
    void colorChanged(QColor color);

private:
    QList<Node*> m_nodes;
    QColor m_color = Qt::blue;
};
