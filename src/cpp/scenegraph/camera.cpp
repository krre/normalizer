#include "camera.h"

Camera::Camera(QObject *parent) : QObject(parent)
{

}

void Camera::setVerticalAngle(float verticalAngle)
{
    if (m_verticalAngle == verticalAngle)
        return;

    m_verticalAngle = verticalAngle;
    updateCamera();
    emit verticalAngleChanged(verticalAngle);
}

void Camera::setAspectRatio(float aspectRatio)
{
    if (m_aspectRatio == aspectRatio)
        return;

    m_aspectRatio = aspectRatio;
    updateCamera();
    emit aspectRatioChanged(aspectRatio);
}

void Camera::setNearPlane(float nearPlane)
{
    if (m_nearPlane == nearPlane)
        return;

    m_nearPlane = nearPlane;
    updateCamera();
    emit nearPlaneChanged(nearPlane);
}

void Camera::setFarPlane(float farPlane)
{
    if (m_farPlane == farPlane)
        return;

    m_farPlane = farPlane;
    updateCamera();
    emit farPlaneChanged(farPlane);
}

void Camera::setPosition(QVector3D position)
{
    if (m_position == position)
        return;

    m_position = position;
    updateCamera();
    emit positionChanged(position);
}

void Camera::updateCamera()
{

}

