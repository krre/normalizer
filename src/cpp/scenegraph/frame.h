#pragma once
#include "node.h"
#include <QtCore>
#include <QtQuick>

class Frame : public Node
{
    Q_OBJECT
    Q_PROPERTY(float width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(float height READ height WRITE setHeight NOTIFY heightChanged)
    Q_PROPERTY(float lineWidth READ lineWidth WRITE setLineWidth NOTIFY lineWidthChanged)

public:
    explicit Frame();
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
};
