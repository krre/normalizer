#include "frame.h"

Frame::Frame()
{

}

void Frame::setWidth(float width)
{
    if (m_width == width)
        return;

    m_width = width;
    emit widthChanged(width);
}

void Frame::setHeight(float height)
{
    if (m_height == height)
        return;

    m_height = height;
    emit heightChanged(height);
}

void Frame::setLineWidth(float lineWidth)
{
    if (m_lineWidth == lineWidth)
        return;

    m_lineWidth = lineWidth;
    emit lineWidthChanged(lineWidth);
}

