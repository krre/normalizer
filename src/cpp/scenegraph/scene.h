#pragma once
#include <QtCore>
#include <QtQml>
#include "node.h"

class Scene : public Node
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)

public:
    explicit Scene();

    QColor color() const { return m_color; }
    void setColor(QColor color);

signals:
    void colorChanged(QColor color);

private:
    QColor m_color = Qt::black;
};
