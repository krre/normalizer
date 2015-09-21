#pragma once
#include <QQuickItem>
#include "camera.h"
#include "scene.h"

class Viewport : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(Camera* camera READ getCamera WRITE setCamera NOTIFY cameraChanged)
    Q_PROPERTY(Scene* scene READ getScene WRITE setScene NOTIFY sceneChanged)

public:
    Viewport();

    Camera* getCamera() const { return m_camera; }
    void setCamera(Camera* camera);
    Scene* getScene() const { return m_scene; }
    void setScene(Scene* scene);

signals:
    void cameraChanged(Camera* camera);
    void sceneChanged(Scene* scene);

protected:
    QSGNode* updatePaintNode(QSGNode*oldNode, UpdatePaintNodeData*);
private:
    Camera* m_camera;
    Scene* m_scene;
};
