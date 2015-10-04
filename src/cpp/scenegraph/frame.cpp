#include "frame.h"

Frame::Frame()
{
    static QSGGeometry::Attribute Vertex3D_Attributes[] = {
        QSGGeometry::Attribute::create(0, 3, GL_FLOAT, true)
    };

    static QSGGeometry::AttributeSet Vertex3D_AttributeSet = {
        1,
        sizeof(Vertex3D),
        Vertex3D_Attributes
    };

    geometry = new QSGGeometry(Vertex3D_AttributeSet, 4, 4);
    geometry->setDrawingMode(GL_LINE_LOOP);

    quint16* indices = geometry->indexDataAsUShort();
    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;
    indices[3] = 3;

    m_geometryNode->setGeometry(geometry);
    m_transformNode.appendChildNode(m_geometryNode);
}

Frame::~Frame()
{
    delete geometry;
}

void Frame::setWidth(float width)
{
    if (m_width == width)
        return;

    m_width = width;
    updateGeometry();
    emit widthChanged(width);
}

void Frame::setHeight(float height)
{
    if (m_height == height)
        return;

    m_height = height;
    updateGeometry();
    emit heightChanged(height);
}

void Frame::setLineWidth(float lineWidth)
{
    if (m_lineWidth == lineWidth)
        return;

    m_lineWidth = lineWidth;
    updateGeometry();
    emit lineWidthChanged(lineWidth);
}

void Frame::updateGeometry()
{
    geometry->setLineWidth(m_lineWidth);

    float x0 = -m_width / 2.0;
    float y0 = -m_height / 2.0;
    float x1 = m_width / 2.0;
    float y1 = m_height / 2.0;
    Vertex3D* vertices = static_cast<Vertex3D*>(geometry->vertexData());
    vertices[0].set(x0, y0, 0);
    vertices[1].set(x0, y1, 0);
    vertices[2].set(x1, y1, 0);
    vertices[3].set(x1, y0, 0);

    m_geometryNode->markDirty(QSGNode::DirtyGeometry);
}

