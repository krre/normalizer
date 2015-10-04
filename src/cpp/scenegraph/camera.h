#pragma once
#include "scene.h"
#include <QtCore>
#include <QtGui>

class Camera : public QObject
{
    Q_OBJECT
    Q_PROPERTY(float verticalAngle READ verticalAngle WRITE setVerticalAngle NOTIFY verticalAngleChanged)
    Q_PROPERTY(float aspectRatio READ aspectRatio WRITE setAspectRatio NOTIFY aspectRatioChanged)
    Q_PROPERTY(float nearPlane READ nearPlane WRITE setNearPlane NOTIFY nearPlaneChanged)
    Q_PROPERTY(float farPlane READ farPlane WRITE setFarPlane NOTIFY farPlaneChanged)

public:
    explicit Camera(QObject *parent = 0);

    float verticalAngle() const { return m_verticalAngle; }
    void setVerticalAngle(float verticalAngle);

    float aspectRatio() const { return m_aspectRatio; }
    void setAspectRatio(float aspectRatio);

    float nearPlane() const { return m_nearPlane; }
    void setNearPlane(float nearPlane);

    float farPlane() const { return m_farPlane; }
    void setFarPlane(float farPlane);

    void setScene(Scene* scene) { m_scene = scene; }

private:
    Scene* m_scene;
    float m_verticalAngle = 45;
    float m_aspectRatio = 1;
    float m_nearPlane = 0;
    float m_farPlane = 100;
    void updateCamera();

signals:
    void verticalAngleChanged(float verticalAngle);
    void aspectRatioChanged(float aspectRatio);
    void nearPlaneChanged(float nearPlane);
    void farPlaneChanged(float farPlane);
};
