#pragma once
#include "geometry.h"
#include <QtCore>
#include <QtQuick>

class Frame : public Geometry
{
    Q_OBJECT
    Q_PROPERTY(float width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(float height READ height WRITE setHeight NOTIFY heightChanged)
    Q_PROPERTY(float lineWidth READ lineWidth WRITE setLineWidth NOTIFY lineWidthChanged)

struct Vertex3D {
    float x;
    float y;
    float z;

    void set(float x_, float y_, float z_) {
        x = x_;
        y = y_;
        z = z_;
    }
};

public:
    explicit Frame();
    ~Frame();
    float width() const { return m_width; }
    void setWidth(float width);

    float height() const { return m_height; }
    void setHeight(float height);

    float lineWidth() const { return m_lineWidth; }
    void setLineWidth(float lineWidth);

signals:
    void widthChanged(float width);
    void heightChanged(float height);
    void lineWidthChanged(float lineWidth);

private:
    float m_width;
    float m_height;
    float m_lineWidth = 1;
    QSGGeometry* geometry;
    void updateGeometry();
};
