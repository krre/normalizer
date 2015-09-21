#include "viewport.h"

Viewport::Viewport()
{
    setFlag(ItemHasContents, true);
}

void Viewport::setCamera(Camera *camera) {
    if (m_camera == camera)
        return;

    m_camera = camera;
    emit cameraChanged(camera);
}

void Viewport::setScene(Scene *scene) {
    if (m_scene == scene)
        return;

    m_scene = scene;
    emit sceneChanged(scene);
}

QSGNode *Viewport::updatePaintNode(QSGNode *oldNode, QQuickItem::UpdatePaintNodeData *)
{
    qDebug() << oldNode;
    return oldNode;
}

