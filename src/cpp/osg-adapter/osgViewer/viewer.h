#pragma once
#include "../camera.h"
#include "../scene.h"
#include <QQuickItem>
#include <osgViewer/Viewer>

class Viewer : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(Camera* camera READ camera WRITE setCamera NOTIFY cameraChanged)
    Q_PROPERTY(Scene* scene READ scene WRITE setScene NOTIFY sceneChanged)

public:
    Viewer();

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
    Camera* m_camera;
    Scene* m_scene;
    osgViewer::Viewer* viewer;
};
