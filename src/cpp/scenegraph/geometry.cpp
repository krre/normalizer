#include "geometry.h"

Geometry::Geometry()
{
    m_geometryNode = new QSGGeometryNode();
    m_geometryNode->setFlag(QSGNode::OwnsGeometry);
    m_geometryNode->setFlag(QSGNode::OwnsMaterial);
    m_geometryNode->setMaterial(&material);
}

Geometry::~Geometry()
{
    delete m_geometryNode;
}

void Geometry::setColor(QColor color)
{
    if (m_color == color)
        return;

    m_color = color;

    material.setColor(color);
    m_geometryNode->markDirty(QSGNode::DirtyMaterial);

    emit colorChanged(color);
}



