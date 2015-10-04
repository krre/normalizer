#pragma once
#include <QQuickItem>
#include "camera.h"
#include "scene.h"

class Viewport : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(Camera* camera READ camera WRITE setCamera NOTIFY cameraChanged)
    Q_PROPERTY(Scene* scene READ scene WRITE setScene NOTIFY sceneChanged)

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
    Viewport();

    Camera* camera() const { return m_camera; }
    void setCamera(Camera* camera);
    Scene* scene() const { return m_scene; }
    void setScene(Scene* scene);

signals:
    void cameraChanged(Camera* camera);
    void sceneChanged(Scene* scene);

protected:
    QSGNode* updatePaintNode(QSGNode* oldNode, UpdatePaintNodeData*);
private:
    Camera* m_camera = nullptr;
    Scene* m_scene = nullptr;
};
