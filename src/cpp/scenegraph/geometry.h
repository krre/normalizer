#pragma once
#include "node.h"
#include <QtCore>
#include <QtQuick>

class Geometry : public Node
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
public:
    Geometry();
    QSGGeometryNode* geometryNode() { return m_geometryNode; }

    QColor color() const { return m_color; }
    void setColor(QColor color);

signals:
    void colorChanged(QColor color);

protected:
    QSGGeometryNode* m_geometryNode;

private:
    QColor m_color;
    QSGFlatColorMaterial* material;
};
