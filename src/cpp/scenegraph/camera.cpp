#include "camera.h"

Camera::Camera(QObject *parent) : QObject(parent)
{

}

void Camera::setColor(QColor color)
{
    if (m_color == color)
        return;

    m_color = color;
    emit colorChanged(color);
}

